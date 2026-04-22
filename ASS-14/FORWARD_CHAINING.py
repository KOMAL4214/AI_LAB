class ForwardChaining:
    def __init__(self, rules, facts):
        self.rules = rules   # [(premises, conclusion)]
        self.facts = set(facts)

    def infer(self, goal):
        print("\nInitial Facts:", self.facts)

        while True:
            new_fact_added = False

            for premises, conclusion in self.rules:
                if set(premises).issubset(self.facts) and conclusion not in self.facts:
                    print(f"Using {premises} -> {conclusion}")
                    self.facts.add(conclusion)
                    new_fact_added = True

                    if conclusion == goal:
                        print("Goal reached:", goal)
                        return True

            if not new_fact_added:
                break

        return goal in self.facts


# -------------------------------
# QUESTION 1(a)
# -------------------------------
rules1 = [
    (['P'], 'Q'),
    (['L', 'M'], 'P'),
    (['A', 'B'], 'L')
]
facts1 = ['A', 'B', 'M']

fc1 = ForwardChaining(rules1, facts1)
print("Result:", fc1.infer('Q'))


# -------------------------------
# QUESTION 1(b)
# -------------------------------
rules2 = [
    (['A'], 'B'),
    (['B'], 'C'),
    (['C'], 'D'),
    (['D', 'E'], 'F')
]
facts2 = ['A', 'E']

fc2 = ForwardChaining(rules2, facts2)
print("Result:", fc2.infer('F'))