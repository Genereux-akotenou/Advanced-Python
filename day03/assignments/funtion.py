from time import sleep
import threading

def run(i):
    while(int(i.value) < 6):
        with i.get_lock():
            current_thread = threading.current_thread()
            print(f"value: {i.value}, from thread: {current_thread.ident}")
            i.value += 1