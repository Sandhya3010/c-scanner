#include <stdio.h>
#include <string.h>

typedef enum {
    TOKPROGRAM,
    TOKIDENTIFIER,
    TOKSEMICOLON,
    TOKWORD,
    TOKEQUALS,
    TOKNUMBER,
    TOKBEGIN,
    TOKEND,
    TOKPERIOD
} TokenType;

typedef struct {
    char kind[10];
    int value;
} AttributeEntry;

typedef struct {
    int lowerBoundAttrIndex;
    int upperBoundAttrIndex;
} AuxiliaryEntry;

typedef struct {
    char lexeme[50];
    TokenType tokenType;
    char dataType[20];
    char scope[20];
    int attrIndex;
    int auxIndex;
} SymbolTableEntry;

#define MAX_SYMBOLS 100
#define MAX_ATTRS 100
#define MAX_AUX 50

SymbolTableEntry symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

AttributeEntry attributeTable[MAX_ATTRS];
int attrCount = 0;

AuxiliaryEntry auxiliaryTable[MAX_AUX];
int auxCount = 0;

int insertAttribute(const char *kind, int value) {
    strcpy(attributeTable[attrCount].kind, kind);
    attributeTable[attrCount].value = value;
    return attrCount++;
}

int insertAuxiliary(int lowerAttrIndex, int upperAttrIndex) {
    auxiliaryTable[auxCount].lowerBoundAttrIndex = lowerAttrIndex;
    auxiliaryTable[auxCount].upperBoundAttrIndex = upperAttrIndex;
    return auxCount++;
}

int insertSymbol(const char *lexeme, TokenType tokenType, const char *dataType, const char *scope, int attrIndex, int auxIndex) {
    strcpy(symbolTable[symbolCount].lexeme, lexeme);
    symbolTable[symbolCount].tokenType = tokenType;
    strcpy(symbolTable[symbolCount].dataType, dataType);
    strcpy(symbolTable[symbolCount].scope, scope);
    symbolTable[symbolCount].attrIndex = attrIndex;
    symbolTable[symbolCount].auxIndex = auxIndex;
    return symbolCount++;
}

void printSymbolTable() {
    printf("\nSYMBOL TABLE:\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-10s %-12d %-10s %-10s AttrIdx:%d AuxIdx:%d\n",
            symbolTable[i].lexeme,
            symbolTable[i].tokenType,
            symbolTable[i].dataType,
            symbolTable[i].scope,
            symbolTable[i].attrIndex,
            symbolTable[i].auxIndex
        );
    }
}

void printAttributeTable() {
    printf("\nATTRIBUTE TABLE:\n");
    for (int i = 0; i < attrCount; i++) {
        printf("%d: Kind=%s Value=%d\n", i, attributeTable[i].kind, attributeTable[i].value);
    }
}

void printAuxiliaryTable() {
    printf("\nAUXILIARY TABLE:\n");
    for (int i = 0; i < auxCount; i++) {
        printf("%d: LowerAttrIdx=%d UpperAttrIdx=%d\n", i, auxiliaryTable[i].lowerBoundAttrIndex, auxiliaryTable[i].upperBoundAttrIndex);
    }
}

int main() {
    // Example: CONST x = 15;
    int attrX = insertAttribute("const", 15);
    insertSymbol("X", TOKIDENTIFIER, "integer", "global", attrX, -1);

    // Example: VAR arr: array[1..10] of integer;
    int lowerAttr = insertAttribute("const", 1);
    int upperAttr = insertAttribute("const", 10);
    int auxArr = insertAuxiliary(lowerAttr, upperAttr);
    insertSymbol("arr", TOKIDENTIFIER, "array", "global", -1, auxArr);

    printSymbolTable();
    printAttributeTable();
    printAuxiliaryTable();

    return 0;
}
