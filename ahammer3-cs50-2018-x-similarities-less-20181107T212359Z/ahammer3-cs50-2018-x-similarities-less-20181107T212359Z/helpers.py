from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    a = set(a.split("\n"))
    b = set(b.split("\n"))

    return a & b


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    a = set(sent_tokenize(a))
    b = set(sent_tokenize(b))

    return a & b


def substr_tokenize(str, n):  # Make a function for substr_tokenize similar to sent_tokenize as nltk.tokenize doesn't implement
    substr = []

    for i in range(len(str) - n + 1):
        substr.append(str[i:i + n])

    return substr


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    a = set(substr_tokenize(a, n))
    b = set(substr_tokenize(b, n))

    return a & b
