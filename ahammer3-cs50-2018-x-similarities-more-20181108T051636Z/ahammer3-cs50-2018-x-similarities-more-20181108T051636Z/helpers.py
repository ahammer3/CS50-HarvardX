from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    # TODO
    # cost matrix here
    cost = [[(0, None) for x in range(len(b) + 1)] for y in range(len(a) + 1)]

    # calculate for the first option
    for i in range(1, len(a) + 1):
        cost[i][0] = (i, Operation.DELETED)

    for j in range(1, len(b) + 1):
        cost[0][j] = (j, Operation.DELETED)

    # calculate minimums
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            dele, _ = cost[i - 1][j]
            ins, _ = cost[i][j - 1]
            sub, _ = cost[i - 1][j - 1]

            dele += 1
            ins += 1

            if a[i - 1] != b[j - 1]:
                sub += 1

            if dele <= ins and dele <= sub:
                cost[i][j] = (dele, Operation.DELETED)
            elif ins <= dele and ins <= sub:
                cost[i][j] = (ins, Operation.INSERTED)
            else:
                cost[i][j] = (sub, Operation.SUBSTITUTED)

    return cost
