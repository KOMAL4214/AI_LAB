from itertools import product

# -------------------------------
# Base Class
# -------------------------------
class Expr:
    def evaluate(self, values):
        pass

    def symbols(self):
        return set()

# -------------------------------
# Symbol Class
# -------------------------------
class Symbol(Expr):
    def __init__(self, name):
        self.name = name

    def evaluate(self, values):
        return values[self.name]

    def symbols(self):
        return {self.name}

    def __repr__(self):
        return self.name

# -------------------------------
# Unary Operation (NOT)
# -------------------------------
class Not(Expr):
    def __init__(self, operand):
        self.operand = operand

    def evaluate(self, values):
        return not self.operand.evaluate(values)

    def symbols(self):
        return self.operand.symbols()

    def __repr__(self):
        return f"~{self.operand}"

# -------------------------------
# Binary Operations
# -------------------------------
class And(Expr):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def evaluate(self, values):
        return self.left.evaluate(values) and self.right.evaluate(values)

    def symbols(self):
        return self.left.symbols().union(self.right.symbols())

    def __repr__(self):
        return f"({self.left} ^ {self.right})"


class Or(Expr):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def evaluate(self, values):
        return self.left.evaluate(values) or self.right.evaluate(values)

    def symbols(self):
        return self.left.symbols().union(self.right.symbols())

    def __repr__(self):
        return f"({self.left} v {self.right})"


class Implies(Expr):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def evaluate(self, values):
        return (not self.left.evaluate(values)) or self.right.evaluate(values)

    def symbols(self):
        return self.left.symbols().union(self.right.symbols())

    def __repr__(self):
        return f"({self.left} -> {self.right})"


class Biconditional(Expr):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def evaluate(self, values):
        return self.left.evaluate(values) == self.right.evaluate(values)

    def symbols(self):
        return self.left.symbols().union(self.right.symbols())

    def __repr__(self):
        return f"({self.left} <-> {self.right})"

# -------------------------------
# Truth Table Function
# -------------------------------
def print_truth_table(expr):
    syms = sorted(list(expr.symbols()))
    print("\nTruth Table for:", expr)
    print(" | ".join(syms) + " | Result")

    for values in product([False, True], repeat=len(syms)):
        val_dict = dict(zip(syms, values))
        result = expr.evaluate(val_dict)
        row = " | ".join(['T' if val_dict[s] else 'F' for s in syms])
        print(row + " | " + ('T' if result else 'F'))

# product → generates combinations
#        ↓
# values → (False, True)
#        ↓
# zip → pairs with symbols
#        ↓
# dict → {'P': False, 'Q': True}
#        ↓
# evaluate → computes result
#        ↓
# print → shows row in truth table


# -------------------------------
# Define Symbols
# -------------------------------
P = Symbol('P')
Q = Symbol('Q')
R = Symbol('R')

# -------------------------------
# Given Expressions
# -------------------------------

expr1 = Implies(Not(P), Q)
expr2 = And(Not(P), Not(Q))
expr3 = Or(Not(P), Not(Q))
expr4 = Implies(Not(P), Not(Q))
expr5 = Biconditional(Not(P), Not(Q))
expr6 = And(Or(P, Q), Implies(Not(P), Q))
expr7 = Implies(Or(P, Q), Not(R))
expr8 = Biconditional(
    Implies(Or(P, Q), Not(R)),
    Implies(And(Not(P), Not(Q)), Not(R))
)
expr9 = Implies(And(Implies(P, Q), Implies(Q, R)), Implies(P, R))
expr10 = Implies(
    Implies(P, Or(Q, R)),
    And(Not(P), And(Not(Q), Not(R)))
)

# -------------------------------
# Print All Truth Tables
# -------------------------------
expressions = [
    expr1, expr2, expr3, expr4, expr5,
    expr6, expr7, expr8, expr9, expr10
]

for expr in expressions:
    print_truth_table(expr)