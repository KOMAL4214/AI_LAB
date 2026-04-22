def resolve(c1, c2):
    resolvents = []
    for literal in c1:
        if f"~{literal}" in c2:
            new_clause = (c1 - {literal}) | (c2 - {f"~{literal}"})
            resolvents.append(new_clause)
        elif literal.startswith("~") and literal[1:] in c2:
            new_clause = (c1 - {literal}) | (c2 - {literal[1:]})
            resolvents.append(new_clause)
    return resolvents


def resolution(kb, goal):
    clauses = [set(c) for c in kb]
    clauses.append({f"~{goal}"})

    print("\nInitial Clauses:", clauses)

    while True:
        new = []
        for i in range(len(clauses)):
            for j in range(i + 1, len(clauses)):
                resolvents = resolve(clauses[i], clauses[j])
                for r in resolvents:
                    if not r:
                        print("Empty clause found → TRUE")
                        return True
                    new.append(r)

        if all(n in clauses for n in new):
            return False

        clauses.extend(new)


# -------------------------------
# QUESTION 3(a)
# -------------------------------
kb1 = [
    {'P', 'Q'},
    {'~P', 'R'},
    {'~Q', 'S'},
    {'~R', 'S'}
]

print("Result:", resolution(kb1, 'S'))


# -------------------------------
# QUESTION 3(b)
# -------------------------------
kb2 = [
    {'~P', 'Q'},
    {'~Q', 'R'},
    {'~S', '~R'},
    {'P'}
]

print("Result:", resolution(kb2, 'S'))