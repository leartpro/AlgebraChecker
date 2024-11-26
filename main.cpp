#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;

using BinaryOp = function<int(int, int)>;

bool isAssociative(const vector<int> &set, const BinaryOp &op) {
    for (int x: set) {
        for (int y: set) {
            for (int z: set) {
                if (op(x, op(y, z)) != op(op(x, y), z)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int findNeutralElement(const vector<int> &set, const BinaryOp &op) {
    for (int e: set) {
        bool isNeutral = true;
        for (int x: set) {
            if (op(e, x) != x || op(x, e) != x) {
                isNeutral = false;
                break;
            }
        }
        if (isNeutral) return e;
    }
    return -1;
}

bool hasInverses(const vector<int> &set, const BinaryOp &op, int neutral) {
    for (int x: set) {
        bool inverseFound = false;
        for (int y: set) {
            if (op(x, y) == neutral && op(y, x) == neutral) {
                inverseFound = true;
                break;
            }
        }
        if (!inverseFound) return false;
    }
    return true;
}

bool isCommutative(const vector<int> &set, const BinaryOp &op) {
    for (int x: set) {
        for (int y: set) {
            if (op(x, y) != op(y, x)) {
                return false;
            }
        }
    }
    return true;
}

bool isDistributive(const vector<int> &set, const BinaryOp &addOp, const BinaryOp &mulOp) {
    for (int x: set) {
        for (int y: set) {
            for (int z: set) {
                if (mulOp(x, addOp(y, z)) != addOp(mulOp(x, y), mulOp(x, z))) {
                    return false;
                }
            }
        }
    }
    return true;
}

int andOp(int x, int y) { return x & y; }

int orOp(int x, int y) { return x | y; }

int xorOp(int x, int y) { return x ^ y; }

int impOp(int x, int y) { return (!x || y); }

int equivOp(int x, int y) { return (x == y); }

int nandOp(int x, int y) { return !(x & y); }

BinaryOp chooseOperation() {
    cout << "Choose an operation for addition:\n";
    cout << "1: AND\n";
    cout << "2: OR\n";
    cout << "3: XOR\n";
    cout << "4: IMPLICATION\n";
    cout << "5: EQUIVALENCE\n";
    cout << "6: NAND\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            return andOp;
        case 2:
            return orOp;
        case 3:
            return xorOp;
        case 4:
            return impOp;
        case 5:
            return equivOp;
        case 6:
            return nandOp;
        default:
            cout << "Invalid choice! Defaulting to AND.\n";
            return andOp;
    }
}

void
checkStructure(const string &structure, const vector<int> &set, const BinaryOp &op1, const BinaryOp &op2 = nullptr) {
    bool isAssoc = isAssociative(set, op1);
    int neutral = findNeutralElement(set, op1);
    bool hasInv = (neutral != -1 && hasInverses(set, op1, neutral));
    bool isComm = isCommutative(set, op1);
    bool isMulAssoc = op2 && isAssociative(set, op2);
    int mulNeutral = op2 ? findNeutralElement(set, op2) : -1;
    bool isDistrib = op2 && isDistributive(set, op1, op2);
    bool isMulComm = op2 && isCommutative(set, op2);

    cout << "Checking " << structure << ":\n";
    if (structure == "monoid") {
        cout << "  Associativity: " << (isAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (neutral != -1 ? "Yes" : "No") << "\n";
    } else if (structure == "group") {
        cout << "  Associativity: " << (isAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (neutral != -1 ? "Yes" : "No") << "\n";
        cout << "  Inverses: " << (hasInv ? "Yes" : "No") << "\n";
    } else if (structure == "abelian group") {
        cout << "  Associativity: " << (isAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (neutral != -1 ? "Yes" : "No") << "\n";
        cout << "  Inverses: " << (hasInv ? "Yes" : "No") << "\n";
        cout << "  Commutativity: " << (isComm ? "Yes" : "No") << "\n";
    } else if (structure == "ring" || structure == "commutative ring") {
        cout << "Addition:\n";
        cout << "  Associativity: " << (isAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (neutral != -1 ? "Yes" : "No") << "\n";
        cout << "  Inverses: " << (hasInv ? "Yes" : "No") << "\n";
        cout << "  Commutativity: " << (isComm ? "Yes" : "No") << "\n";
        cout << "Multiplication:\n";
        cout << "  Associativity: " << (isMulAssoc ? "Yes" : "No") << "\n";
        if (structure == "commutative ring") {
            cout << "  Commutativity: " << (isMulComm ? "Yes" : "No") << "\n";
        }
    } else if (structure == "field") {
        cout << "Addition:\n";
        cout << "  Associativity: " << (isAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (neutral != -1 ? "Yes" : "No") << "\n";
        cout << "  Inverses: " << (hasInv ? "Yes" : "No") << "\n";
        cout << "  Commutativity: " << (isComm ? "Yes" : "No") << "\n";
        cout << "Multiplication:\n";
        cout << "  Associativity: " << (isMulAssoc ? "Yes" : "No") << "\n";
        cout << "  Neutral Element: " << (mulNeutral != -1 ? "Yes" : "No") << "\n";
        cout << "Distributive Property: " << (isDistrib ? "Yes" : "No") << "\n";
    }
}

int main() {
    vector<int> set = {0, 1};
    cout << "Choose an algebraic structure:\n";
    cout << "1: Monoid\n";
    cout << "2: Group\n";
    cout << "3: Abelian Group\n";
    cout << "4: Ring\n";
    cout << "5: Commutative Ring\n";
    cout << "6: Field\n";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= 5) {
        BinaryOp op1 = chooseOperation();
        BinaryOp op2 = nullptr;
        if (choice >= 4) { // only Ring or Field
            cout << "Choose a second operation for multiplication:\n";
            op2 = chooseOperation();
        }

        switch (choice) {
            case 1:
                checkStructure("monoid", set, op1);
                break;
            case 2:
                checkStructure("group", set, op1);
                break;
            case 3:
                checkStructure("abelian group", set, op1);
                break;
            case 4:
                checkStructure("ring", set, op1, op2);
                break;
            case 5:
                checkStructure("commutative ring", set, op1, op2);
                break;
            case 6:
                checkStructure("field", set, op1, op2);
                break;
            default:
                break;
        }
    } else {
        cout << "Invalid choice!\n";
    }
    return 0;
}