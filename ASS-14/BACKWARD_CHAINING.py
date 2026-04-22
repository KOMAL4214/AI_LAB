class BackwardChaining:
    def __init__(self, rules, facts):
        self.rules = rules
        self.facts = set(facts)

    def prove(self, goal):
        print(f"Trying to prove: {goal}")

        if goal in self.facts:
            print(f"{goal} is a known fact")
            return True

        for premises, conclusion in self.rules:
            if conclusion == goal:
                print(f"Checking rule {premises} -> {goal}")
                if all(self.prove(p) for p in premises):
                    return True

        return False


# -------------------------------
# QUESTION 2(a)
# -------------------------------
rules3 = [
    (['P'], 'Q'),
    (['R'], 'Q'),
    (['A'], 'P'),
    (['B'], 'R')
]
facts3 = ['A', 'B']

bc1 = BackwardChaining(rules3, facts3)
print("Result:", bc1.prove('Q'))


# -------------------------------
# QUESTION 2(b)
# -------------------------------
rules4 = [
    (['A'], 'B'),
    (['B', 'C'], 'D'),
    (['E'], 'C')
]
facts4 = ['A', 'E']

bc2 = BackwardChaining(rules4, facts4)
print("Result:", bc2.prove('D'))