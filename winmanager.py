import ctypes

def gettitle():
    lib = ctypes.windll.LoadLibrary("user32.dll")
    handle = lib.GetForegroundWindow()   # get window handle
    buffer = ctypes.create_unicode_buffer(255)  # title buffer
    lib.GetWindowTextW(handle, buffer, ctypes.sizeof(buffer))  # save title
    
    return buffer.value    # return buffer