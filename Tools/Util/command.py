import subprocess

def run_command(command, cwd=None) -> tuple[int, str]:
    """Run a command and return (return_code, stdout+stderr)."""
    
    result = subprocess.run(
        command,
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        cwd=cwd
    )
    
    return (result.returncode, result.stdout)

def stream_command(command, cwd=None):
    """Run a command and stream output to console. Returns the return code."""
    
    process = subprocess.Popen(
        command,
        shell=True,
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