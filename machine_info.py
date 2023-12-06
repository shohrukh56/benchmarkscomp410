import platform
import psutil

def get_machine_info():
    system_info = platform.uname()
    cpu_info = platform.processor()

    print("System Information:")
    print(f"System: {system_info.system}")
    print(f"Node Name: {system_info.node}")
    print(f"Release: {system_info.release}")
    print(f"Version: {system_info.version}")
    print(f"Machine: {system_info.machine}")

    print("\nCPU Information:")
    print(f"Processor: {cpu_info}")

if __name__ == "__main__":
    get_machine_info()
