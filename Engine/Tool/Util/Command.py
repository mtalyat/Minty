import subprocess

def run_command(command, cwd=None) -> tuple[int, str]:
    """Run a command and return (return_code, stdout+stderr)."""
    use_shell = isinstance(command, str)
    
    result = subprocess.run(
        command,
        shell=use_shell,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        cwd=cwd
    )
    
    return (result.returncode, result.stdout)

def stream_command(command, cwd=None):
    """Run a command and stream output to console. Returns the return code."""
    use_shell = isinstance(command, str)
    
    process = subprocess.Popen(
        command,
        shell=use_shell,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1, # line buffered
        cwd=cwd
    )
    
    for line in process.stdout:
        yield line.rstrip('\n')

    process.wait()
    return process.returncode

def print_command(command, cwd=None):
    """Run a command and print output to console. Returns the return code."""
    stream = stream_command(command, cwd)
    while True:
        try:
            line = next(stream)
            print(line)
        except StopIteration as stop:
            return int(stop.value) if stop.value is not None else 0