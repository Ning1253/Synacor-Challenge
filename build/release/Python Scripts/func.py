from functools import lru_cache
from sys import setrecursionlimit
from threading import stack_size, Thread

setrecursionlimit(100000000)
stack_size(0xFFFFFFF)

@lru_cache(maxsize = None)
def func(a, b, N):
    if a == 0:
        return (b + 1) & 32767
    if b == 0:
        return func(a - 1, N, N)
    return func(a - 1, func(a, b - 1, N), N)

class ThreadWithReturnValue(Thread):
    def __init__(self, group=None, target=None, name=None,
                 args=(), kwargs={}, Verbose=None):
        Thread.__init__(self, group, target, name, args, kwargs)
        self._return = None
    def run(self):
        if self._target is not None:
            self._return = self._target(*self._args,
                                                **self._kwargs)
    def join(self, *args):
        Thread.join(self, *args)
        return self._return

for N in range(32768):
    t = ThreadWithReturnValue(target=func, args = (4, 1, N))
    t.start()

    if t.join() == 6:
        print(f"{N} is correct!!")
        input()
    else:
        print(f"{N} is wrong!!")
    
    func.cache_clear()