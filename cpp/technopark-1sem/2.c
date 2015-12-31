/**
 Требуется написать программу, которая способна вычислять логическе выражения. Выражения могут содержать: 1) знаки операций 'and' - и, 'or' - или, 'not' - отрицание, 'xor' - сложение по модулю 2 2) Скобки '(', ')' 4) Логические значения 'True', 'False' 3) Так-же требуется реализовать возможность задания переменных которые могут состоять только из маленьких букв латинского алфавита к примеру 'x=True' 4) необходимо учитывать приоритеты операций, пробелы ничего не значат 5) Если в выражении встретилась ошибка, в том числе необъявленная переменная требуется вывести в стандартный поток вывода "[error]"
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Ассоциативный массив (строка => логическое значение)
 * Ключ массива не может быть NULL
 */
struct AssocArray {
    char **names; // ключи
    _Bool *values; // значения

    size_t length; // длина выделенной памяти
    size_t elements; // действительное количество элементов
};

// задание элемента ассоциативного массива
int AssocArray_set(struct AssocArray *, const char *, const _Bool);
// получение элемента ассоциативного массива
int AssocArray_get(struct AssocArray *, const char *);
// вывод ассоциативного массива
void AssocArray_show(struct AssocArray *);
// создание ассоциативного массива
struct AssocArray *AssocArray_init();
// очистка памяти после ассоциативного массива
void AssocArray_clear(struct AssocArray *);

// минимальная длина выделенной памяти для ассоциативного массива
#define ASSOC_ARRAY_INIT_LENGTH 10
// значение "произошла ошибка" для ассоциативного массива
#define ASSOC_ARRAY_ERROR -1
/**
 * =========
 */

/**
 * Стек строк с возможностями массива (получение/задание элементов по индексу)
 * В стеке не может быть строки NULL
 */
struct StackArray {
    char **values; // значения

    size_t length; // длина выделенной памяти
    size_t elements; // действительное количество элементов
};

// добавление элемента на вершину стека
int StackArray_push(struct StackArray *, const char *);
// получение элемента с вершины стека (и удаление его из стека)
char *StackArray_pop(struct StackArray *);
// запись элемента в стек на определенную позицию
int StackArray_set(struct StackArray *, size_t, const char *);
// получение элемента из стека с определенной позицией
char *StackArray_get(struct StackArray *, size_t);
// вывод стека
void StackArray_show(struct StackArray *);
// создание стека
struct StackArray *StackArray_init();
// очистка памяти после стека
void StackArray_clear(struct StackArray *);

// минимальная длина выделенной памяти для стека
#define STACK_ARRAY_INIT_LENGTH 10
// значение "произошла ошибка" для стека
#define STACK_ARRAY_ERROR -1
/**
 * =========
 */

// копирование строки
char *strCopy(const char *);
// копирование строки с обрезанием
char *substrCopy(const char *, size_t maxLen);

// минимальная длина выделенной памяти для вводимой строки
#define INPUT_STRING_INIT_LENGTH 10
// ввод строки
char *inputString();

// удаление символов в строке с начала и с конца
// !!! Изменяет переданную строку !!!
char *trim(char *, char);
// удаление пробелов в строке с начала и с конца
// !!! Изменяет переданную строку !!!
char *trimSpaces(char *);

// минимальная длина выделенной памяти для текста (для "исполнения"), разделенного по \n и ;
#define EVALUATE_TEXT_INIT_LENGTH 3

// константы для evaluate*, execute* функций
#define EVALUATE_TRUE "True"
#define EVALUATE_FALSE "False"
#define EVALUATE_ERROR -1
#define EVALUATE_OPERATOR_EQUAL "="
#define EVALUATE_OPERATOR_EQUAL_CHAR '='
#define EVALUATE_OPERATOR_BRACKET_OPEN "("
#define EVALUATE_OPERATOR_BRACKET_OPEN_CHAR '('
#define EVALUATE_OPERATOR_BRACKET_CLOSE ")"
#define EVALUATE_OPERATOR_BRACKET_CLOSE_CHAR ')'
#define EVALUATE_OPERATOR_AND "and"
#define EVALUATE_OPERATOR_AND_PRIORITY 8
#define EVALUATE_OPERATOR_OR "or"
#define EVALUATE_OPERATOR_OR_PRIORITY 7
#define EVALUATE_OPERATOR_XOR "xor"
#define EVALUATE_OPERATOR_XOR_PRIORITY 9
#define EVALUATE_OPERATOR_NOT "not"
#define EVALUATE_OPERATOR_NOT_PRIORITY 10
#define EVALUATE_OPERATOR_DEFAULT_PRIORITY -1

// "исполнение" текста
int evaluateText(char *);
// "исполнение" строки
int evaluateExpression(char *, struct AssocArray *);
// выполнение операций согласно стеку операндов
int executeOperandsStack(struct StackArray *, struct AssocArray *);

// получение приоритета оператора
int getOperatorPriority(const char *);
// определение, является ли строка оператором
_Bool isOperator(const char *);

int main() {
    // ввод текста
    char *text = inputString();

    if(text != NULL) {
        // "исполняем" текст
        int result = evaluateText(text);

        if(result == 0) {
            printf("False");
        }
        else if(result == 1) {
            printf("True");
        }
        else
        {
            // не удалось "исполнить" текст
            printf("[error]");
        }
    }
    else
    {
        // не удалось ввести текст
        printf("[error]");
    }

    free(text);
    return 0;
}

/*
 * Задание элемента ассоциативного массива
 */
int AssocArray_set(struct AssocArray *this, const char *key, const _Bool val) {
    assert(this != NULL);
    assert(key != NULL);

    size_t index = -1;

    // ищем ключ var в уже существующих ключах
    for(size_t i = 0; i < this->elements; i++) {
        if(!strcmp(key, this->names[i])) {
            index = i;
        }
    }

    if(index != (size_t) -1) {
        // ключ var уже существует
        this->values[index] = val;
    }
    else
    {
        if(this->elements == this->length) {
            // удваиваем память, если достигли максимальное кол-во элементов
            size_t newLength = this->length * 2 * sizeof(char *);
            char **newNamesMemory = (char **) realloc(this->names, newLength);
            if(newNamesMemory == NULL) {
                return ASSOC_ARRAY_ERROR;
            }
            this->names = newNamesMemory;

            _Bool *newValuesMemory = (_Bool *) realloc(this->values, newLength);
            if(newValuesMemory == NULL) {
                return ASSOC_ARRAY_ERROR;
            }
            this->values = newValuesMemory;

            this->length = newLength;
        }

        // копируем ключ
        char *keyCopy = (char *) malloc(sizeof(char) * (strlen(key) + 1));
        if(keyCopy == NULL) {
            return ASSOC_ARRAY_ERROR;
        }

        strcpy(keyCopy, key);

        // сохраняем ключ и значение
        size_t newIndex = this->elements++;
        this->names[newIndex] = keyCopy;
        this->values[newIndex] = val;
    }

    return 0;
}

/*
 * Получение элемента ассоциативного массива
 */
int AssocArray_get(struct AssocArray *this, const char *key) {
    assert(this != NULL);
    assert(key != NULL);

    size_t index = -1;

    // ищем ключ var
    for(size_t i = 0; i < this->elements; i++) {
        if(!strcmp(key, this->names[i])) {
            index = i;
        }
    }

    if(index == (size_t) -1) {
        // ключ не найден
        return ASSOC_ARRAY_ERROR;
    }

    // ключ найден, возвращаем
    return this->values[index];
}

/*
 * Вывод ассоциативного массива
 */
void AssocArray_show(struct AssocArray *this) {
    assert(this != NULL);

    printf("\n[\n");
    for(size_t i = 0; i < this->elements; i++) {
        printf("'%s' ==> '%d'\n", this->names[i], this->values[i]);
    }
    printf("]\n");
}

/*
 * Создание ассоциативного массива
 */
struct AssocArray *AssocArray_init() {
    struct AssocArray *this = (struct AssocArray *) malloc(sizeof(struct AssocArray));
    if(this == NULL) {
        return NULL;
    }

    size_t length = ASSOC_ARRAY_INIT_LENGTH;
    this->names = (char **) malloc(length * sizeof(char *));
    if(this->names == NULL) {
        free(this);
        return NULL;
    }

    this->values = (_Bool *) malloc(length * sizeof(_Bool));
    if(this->values == NULL) {
        free(this->names);
        free(this);
        return NULL;
    }

    this->length = length;
    this->elements = 0;

    return this;
}
/*
 * Очистка памяти после ассоциативного массива
 */
void AssocArray_clear(struct AssocArray *this) {
    assert(this != NULL);

    for(size_t i = 0; i < this->elements; i++) {
        free(this->names[i]);
    }
    free(this->names);
    free(this->values);
    free(this);
}



/*
 * Добавление элемента на вершину стека
 */
int StackArray_push(struct StackArray *this, const char *val) {
    assert(this != NULL);
    assert(val != NULL);

    if(this->length == this->elements) {
        // удваиваем память, если достигли максимальное кол-во элементов
        size_t newLength = this->length * 2 * sizeof(char *);
        char **newMemory = (char **) realloc(this->values, newLength);
        if(newMemory == NULL) {
            return STACK_ARRAY_ERROR;
        }
        this->values = newMemory;
        this->length = newLength;
    }

    // копируем строку
    char *valCopy = (char *) malloc(sizeof(char) * (strlen(val) + 1));
    if(valCopy == NULL) {
        return STACK_ARRAY_ERROR;
    }

    strcpy(valCopy, val);

    // сохраняем строку
    size_t newIndex = this->elements++;
    this->values[newIndex] = valCopy;

    return 0;
}

/*
 * Получение элемента с вершины стека (и удаление его из стека)
 */
char *StackArray_pop(struct StackArray *this) {
    assert(this != NULL);

    if(this->elements == 0) {
        return NULL;
    }
    return this->values[(this->elements--) - 1];
}

/*
 * Запись элемента в стек на определенную позицию
 */
int StackArray_set(struct StackArray *this, size_t index, const char *val) {
    assert(this != NULL);
    assert(index < this->elements);
    assert(val != NULL);

    char *valCopy = (char *) malloc(sizeof(char) * (strlen(val) + 1));
    if(valCopy == NULL) {
        return STACK_ARRAY_ERROR;
    }

    strcpy(valCopy, val);

    free(this->values[index]);
    this->values[index] = valCopy;

    return 0;
}

/*
 * Получение элемента из стека с определенной позицией
 */
char *StackArray_get(struct StackArray *this, size_t index) {
    assert(this != NULL);
    assert(index < this->elements);

    return this->values[index];
}

/*
 * Вывод стека
 */
void StackArray_show(struct StackArray *this) {
    assert(this != NULL);

    printf("\n{{\n");
    for(size_t i = 0; i < this->elements; i++) {
        printf("'%zu' ==> '%s'\n", i, this->values[i]);
    }
    printf("}}\n");
}

/*
 * Создание стека
 */
struct StackArray *StackArray_init() {
    struct StackArray *this = (struct StackArray *) malloc(sizeof(struct StackArray));
    if(this == NULL) {
        return NULL;
    }

    // начальная длина массива
    size_t length = STACK_ARRAY_INIT_LENGTH;

    // выделение памяти под массив
    this->values = (char **) malloc(length * sizeof(char *));
    if(this->values == NULL) {
        free(this);
        return NULL;
    }

    this->length = length;
    this->elements = 0;

    return this;
}

/*
 * Очистка памяти после стека
 */
void StackArray_clear(struct StackArray *this) {
    assert(this != NULL);
    for(size_t i = 0; i < this->elements; i++) {
        free(this->values[i]);
    }
    free(this->values);
    free(this);
}


/*
 * Копирование строки
 */
char *strCopy(const char *source) {
    if(source == NULL) {
        return NULL;
    }

    size_t len = strlen(source);
    char *str = (char *) malloc(sizeof(char) * (len + 1));
    if(!str) {
        return NULL;
    }

    strcpy(str, source);
    return str;
}

/*
 * Копирование строки с обрезанием до maxLen
 */
char *substrCopy(const char *source, size_t maxLen) {
    if(source == NULL) {
        return NULL;
    }

    size_t len = strlen(source);
    if(maxLen < len) {
        len = maxLen;
    }
    char *str = (char *) malloc(sizeof(char) * (len + 1));

    if(!str) {
        return NULL;
    }

    size_t i = 0;
    for(i = 0; i < len; i++) {
        str[i] = source[i];
    }
    str[i] = '\0';
    return str;
}

/*
 * Ввод строки
 */
char *inputString() {
    char *str = NULL, // полученная строка
         c; // текущий символ

    size_t i = 0, // номер текущего символа в строке
           length = INPUT_STRING_INIT_LENGTH; // длина выделенной памяти

    while(scanf("%c", &c) == 1) {
        char *newStr = str;
        if(str == NULL) {
            // первый символ
            newStr = (char *) malloc(sizeof(char) * length);
        }
        else if(i == length - 2)
        {
            length *= 2;
            newStr = (char *) realloc(str, sizeof(char) * length);
        }

        if(newStr == NULL) {
            // не удалось выделить память
            free(str);
            return NULL;
        }
        str = newStr;

        // записываем символ
        str[i++] = c;
    }

    if(str != NULL) {
        // конец строки
        str[i] = '\0';
    }

    return str;
}

/*
 * Удаление символов в строке с начала и с конца
 * !!! Изменяет переданную строку !!!
 */
char *trim(char *source, char symbol) {
    if(source == NULL) {
        return NULL;
    }
    size_t i = 0,
           j,
           strLen = strlen(source);
    while(source[i] == symbol) {
        i++;
    }
    if(i > 0) {
        for(j = 0; j < strLen; j++) {
            source[j] = source[j+i];
            if(source[j+i] == '\0') {
                break;
            }
        }
        source[j] = '\0';
    }

    strLen = strlen(source);
    if(strLen > 0) {
        i = strLen - 1;
        while(source[i] == symbol) {
            i--;
        }
        if(i < strLen - 1) {
            source[i+1] = '\0';
        }
    }
    return source;
}

/*
 * Удаление пробелов в строке с начала и с конца
 * !!! Изменяет переданную строку !!!
 */
char *trimSpaces(char *source) {
    return trim(source, ' ');
}

/*
 * "Исполнение" текста
 */
int evaluateText(char *text) {
    assert(text != NULL);

    struct AssocArray *vars = AssocArray_init();
    if(vars == NULL) {
        return EVALUATE_ERROR;
    }

    size_t partsCount = 0,
           partsMemory = EVALUATE_TEXT_INIT_LENGTH;

    char **parts = (char **) malloc(sizeof(char *) * EVALUATE_TEXT_INIT_LENGTH);

    if(parts == NULL) {
        AssocArray_clear(vars);
        return EVALUATE_ERROR;
    }

    char *textPart = strtok(text, ";\n");
    while(textPart != NULL) {
        if(strlen(textPart) > 0) {
            if(partsMemory == partsCount) {
                partsMemory *= 2;
                char **newParts = (char **) realloc(parts, partsMemory * sizeof(char *));
                if(newParts == NULL) {
                    free(parts);
                    AssocArray_clear(vars);
                    return EVALUATE_ERROR;
                }
                parts = newParts;
            }
            parts[partsCount++] = textPart;
        }
        textPart = strtok(NULL, ";\n");
    }

    int res = EVALUATE_ERROR;

    for(size_t i = 0; i < partsCount; i++) {
        char *part = strCopy(parts[i]);
        if(part == NULL) {
            free(parts);
            AssocArray_clear(vars);
            return EVALUATE_ERROR;
        }
        res = evaluateExpression(part, vars);
        free(part);

        if(res == EVALUATE_ERROR) {
            break;
        }
    }

    free(parts);
    AssocArray_clear(vars);

    return res;
}

/*
 * "Исполнение" строки
 */
int evaluateExpression(char *expr, struct AssocArray *vars) {
    assert(expr != NULL);
    assert(vars != NULL);

    // ищем знак =, возможно это строка с присвоением
    size_t exprLength = strlen(expr);
    for(size_t i = 0; i < exprLength; i++) {
        if(expr[i] == EVALUATE_OPERATOR_EQUAL_CHAR) {
            char *varName = trimSpaces(substrCopy(expr, i));

            if(varName == NULL) {
                return EVALUATE_ERROR;
            }
            char *varExpr = trimSpaces(substrCopy(expr + i + 1, exprLength - i));

            if(varExpr == NULL) {
                free(varName);
                return EVALUATE_ERROR;
            }

            int val = evaluateExpression(varExpr, vars);
            if(val != EVALUATE_ERROR) {
                if(AssocArray_set(vars, varName, val) == ASSOC_ARRAY_ERROR) {
                    free(varName);
                    free(varExpr);
                    return EVALUATE_ERROR;
                }
            }

            free(varName);
            free(varExpr);
            return val;
        }
    }

    struct StackArray *operators = StackArray_init();
    if(operators == NULL) {
        return EVALUATE_ERROR;
    }
    struct StackArray *operands = StackArray_init();
    if(operands == NULL) {
        free(operators);
        return EVALUATE_ERROR;
    }

    char *token = strtok(expr, " ");
    size_t tokenLength = (token == NULL) ? 0 : strlen(token);
    while(token != NULL) {
        tokenLength = strlen(token);
        if(tokenLength > 0) {
            // обрабатываем открывающие скобки
            while(token[0] == EVALUATE_OPERATOR_BRACKET_OPEN_CHAR) {
                tokenLength = strlen(token);
                if(tokenLength == 0) {
                    break;
                }
                if(StackArray_push(operators, EVALUATE_OPERATOR_BRACKET_OPEN) == STACK_ARRAY_ERROR) {
                    StackArray_clear(operators);
                    StackArray_clear(operands);
                    return EVALUATE_ERROR;
                }
                trim(token, EVALUATE_OPERATOR_BRACKET_OPEN_CHAR);
            }

            // обрабатываем операторы и операнды
            char *tokenCopy = trim(substrCopy(token, tokenLength), EVALUATE_OPERATOR_BRACKET_CLOSE_CHAR);
            if(tokenCopy == NULL) {
                StackArray_clear(operators);
                StackArray_clear(operands);
                return EVALUATE_ERROR;
            }

            if(isOperator(tokenCopy)) {
                // нашли оператор
                char *operator = NULL;
                while(operators->elements > 0) {
                    // все операторы большего или равного приоритета заносим в стек операндов
                    operator = StackArray_pop(operators);
                    if( operator == NULL
                        ||
                        getOperatorPriority(operator) < getOperatorPriority(tokenCopy)
                        ) {
                        free(operator);
                        break;
                    }
                    if(StackArray_push(operands, operator) == STACK_ARRAY_ERROR) {
                        StackArray_clear(operators);
                        StackArray_clear(operands);
                        free(operator);
                        return EVALUATE_ERROR;
                    }
                    free(operator);
                }
                // заносим текущий оператор в стек операторов
                if(StackArray_push(operators, tokenCopy) == STACK_ARRAY_ERROR) {
                    StackArray_clear(operators);
                    StackArray_clear(operands);
                    free(tokenCopy);
                    return EVALUATE_ERROR;
                }
            }
            else if(strlen(tokenCopy) > 0) {
                // заносим операнд в стек операндов
                if(StackArray_push(operands, tokenCopy) == STACK_ARRAY_ERROR) {
                    StackArray_clear(operators);
                    StackArray_clear(operands);
                    free(tokenCopy);
                    return EVALUATE_ERROR;
                }
            }

            // обрабатываем закрывающие скобки
            while(token && (tokenLength = strlen(token)) > 0 && token[tokenLength - 1] == EVALUATE_OPERATOR_BRACKET_CLOSE_CHAR) {
                char *topToken = NULL;
                while((topToken = StackArray_pop(operators)) != NULL &&
                        strcmp(topToken, EVALUATE_OPERATOR_BRACKET_CLOSE)) {
                    if(StackArray_push(operands, topToken) == STACK_ARRAY_ERROR) {
                        StackArray_clear(operators);
                        StackArray_clear(operands);
                        free(topToken);
                        free(tokenCopy);
                        return EVALUATE_ERROR;
                    }
                    free(topToken);
                    topToken = NULL;
                }
                free(topToken);
                token[tokenLength - 1] = '\0';
            }
            free(tokenCopy);
        }
        token = strtok(NULL, " ");
    }

    while(operators->elements > 0) {
        char *operator = StackArray_pop(operators);
        if(StackArray_push(operands, operator) == STACK_ARRAY_ERROR) {
            StackArray_clear(operators);
            StackArray_clear(operands);
            free(operator);
            return EVALUATE_ERROR;
        }
        free(operator);
    }

    int res = executeOperandsStack(operands, vars);

    // очистка памяти после стеков
    StackArray_clear(operators);
    StackArray_clear(operands);

    return res;
}

/**
 * Выполнение операций согласно стеку операндов
 */
int executeOperandsStack(struct StackArray *stack, struct AssocArray *vars) {
    assert(stack != NULL);
    assert(vars != NULL);

    for(size_t i = 0; i < stack->elements; i++) {
        char *cur = StackArray_get(stack, i);

        if(!isOperator(cur) && strcmp(cur, EVALUATE_TRUE) != 0 && strcmp(cur, EVALUATE_FALSE) != 0 && AssocArray_get(vars, cur) == ASSOC_ARRAY_ERROR) {
            return EVALUATE_ERROR;
        }

        if(!isOperator(cur)) {
            continue;
        }

        if(!strcmp(cur, EVALUATE_OPERATOR_NOT)) {
            // унарный оператор NOT
            char *operand = StackArray_get(stack, i - 1);
            int eval = evaluateExpression(operand, vars);

            if(eval != EVALUATE_ERROR) {
                if(StackArray_set(stack, i, (!eval ? EVALUATE_TRUE : EVALUATE_FALSE)) == STACK_ARRAY_ERROR) {
                    return EVALUATE_ERROR;
                }
            }
            else
            {
                return EVALUATE_ERROR;
            }
        }
        else
        {
            // бинарные операторы
            char *operand1 = StackArray_get(stack, i - 1);
            char *operand2 = StackArray_get(stack, i - 2);

            int eval1 = evaluateExpression(operand1, vars);
            int eval2 = evaluateExpression(operand2, vars);

            int res = EVALUATE_ERROR;

            if(eval1 == EVALUATE_ERROR || eval2 == EVALUATE_ERROR) {
                return EVALUATE_ERROR;
            }
            else if(!strcmp(cur, EVALUATE_OPERATOR_XOR)) {
                // XOR
                res = eval1 ^ eval2;
            }
            else if(!strcmp(cur, EVALUATE_OPERATOR_OR)) {
                // OR
                res = eval1 || eval2;
            }
            else if(!strcmp(cur, EVALUATE_OPERATOR_AND)) {
                // AND
                res = eval1 && eval2;
            }

            if(res == 0 || res == 1) {
                if(StackArray_set(stack, i, res ? EVALUATE_TRUE : EVALUATE_FALSE) == STACK_ARRAY_ERROR) {
                    return EVALUATE_ERROR;
                }
            }
            else
            {
                return EVALUATE_ERROR;
            }
        }
    }

    char *lastVal = StackArray_pop(stack);
    int result = EVALUATE_ERROR;
    if(lastVal != NULL) {
        if(!strcmp(lastVal, EVALUATE_TRUE)) {
            result = 1;
        }
        else if(!strcmp(lastVal, EVALUATE_FALSE)) {
            result = 0;
        }
        else
        {
            result = AssocArray_get(vars, lastVal);
        }
    }
    free(lastVal);

    return result;
}

/*
 * Получение приоритета оператора
 */
int getOperatorPriority(const char *operator) {
    if(operator == NULL) {
        return EVALUATE_OPERATOR_DEFAULT_PRIORITY;
    }

    if(!strcmp(operator, EVALUATE_OPERATOR_NOT)) {
        return EVALUATE_OPERATOR_NOT_PRIORITY;
    }
    else if(!strcmp(operator, EVALUATE_OPERATOR_XOR)) {
        return EVALUATE_OPERATOR_XOR_PRIORITY;
    }
    else if(!strcmp(operator, EVALUATE_OPERATOR_AND)) {
        return EVALUATE_OPERATOR_AND_PRIORITY;
    }
    else if(!strcmp(operator, EVALUATE_OPERATOR_OR)) {
        return EVALUATE_OPERATOR_OR_PRIORITY;
    }
    return EVALUATE_OPERATOR_DEFAULT_PRIORITY;
}

/*
 * Определение, является ли строка оператором
 */
_Bool isOperator(const char *operator) {
    return getOperatorPriority(operator) != EVALUATE_OPERATOR_DEFAULT_PRIORITY;
}
