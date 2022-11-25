import asyncio

async def echo(msg):
    process = await asyncio.create_subprocess_exec(
        'cat',
        stdin=asyncio.subprocess.PIPE,
        stdout=asyncio.subprocess.PIPE
    )
    print('Writing {!r} ...'.format(msg))
    process.stdin.write(msg.encode() + b'\n')
    data = await process.stdout.readline()
    reply = data.decode().strip()
    print('Received {!r}'.format(reply))
    process.terminate()
    code = await process.wait()
    print('Terminated with code {}'.format(code))

loop = asyncio.get_event_loop()
loop.run_until_complete(echo('hello!'))
loop.close()