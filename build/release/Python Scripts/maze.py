from collections import deque

maze = [["22", "-", "9", "*"],
        ["+", "4", "-", "18"],
        ["4", "*", "11", "*"], 
        ["*", "8", "-", "1"]]

start = (0, 0)
queue = deque()
queue.append([start])

def check(path):
    num = 22
    if path[-1] != (3, 3):
        return False
    
    for i in range(1, len(path), 2):
        num = eval(str(num) + maze[path[i][1]][path[i][0]] + maze[path[i + 1][1]][path[i + 1][0]])

    if num == 30:
        return True

def get_pos(pos):
    array = []
    if pos[0] > 0 and pos != (1, 0): array.append((pos[0] - 1, pos[1]))
    if pos[0] < 3: array.append((pos[0] + 1, pos[1]))
    if pos[1] > 0 and pos != (0, 1): array.append((pos[0], pos[1] - 1))
    if pos[1] < 3: array.append((pos[0], pos[1] + 1))

    return array

while queue:
    cpath = queue.popleft()
    if check(cpath):
        print(cpath)
        break
    if cpath[-1] != (3, 3):
        for pos in get_pos(cpath[-1]):
            queue.append(cpath + [pos])


    