import serial
import win32com.client
import pythoncom
import time
import threading
import queue

# ===== الإعدادات =====
PORT = 'COM3'         # ← غيّرها حسب عندك
BAUD = 9600
DEDUP_TIME = 2.0      # ثواني — منع تكرار نفس الجملة
# =====================

# ===== Queue للصوت =====
speak_queue = queue.Queue()


# ===== Thread للنطق =====
def speaker_thread():
    # ⚠️ مهم جداً — COM initialization في الـ thread
    pythoncom.CoInitialize()

    speaker = win32com.client.Dispatch("SAPI.SpVoice")
    speaker.Rate = 0
    speaker.Volume = 100

    while True:
        text = speak_queue.get()
        if text is None:
            break
        try:
            speaker.Speak(text)
        except Exception as e:
            print(f"[Speak Error] {e}")
        speak_queue.task_done()

    pythoncom.CoUninitialize()


# شغّل الـ thread
t = threading.Thread(target=speaker_thread, daemon=True)
t.start()


# ===== الاتصال بالـ Serial =====
print(f"Connecting to {PORT}...")
ser = serial.Serial(PORT, BAUD, timeout=1)
print(f"Connected! Listening...\n")


# ===== متغيرات dedup =====
last_message = ""
last_time = 0


# ===== الحلقة الرئيسية =====
try:
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()

        if not line:
            continue

        now = time.time()

        # لو نفس الرسالة ومر على وقتها أقل من DEDUP_TIME → تجاهلها
        if line == last_message and (now - last_time) < DEDUP_TIME:
            print(f"[Skip] {line}")
            continue

        print(f"[Voice] {line}")
        last_message = line
        last_time = now

        # ضيف في الـ queue
        speak_queue.put(line)

except KeyboardInterrupt:
    print("\nStopped.")
finally:
    speak_queue.put(None)
    ser.close()