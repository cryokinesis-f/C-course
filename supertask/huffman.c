#include <stdio.h>   
#include <stdlib.h>
#include <stdint.h>

#define MAX_SYMBOLS 256  // Максимальное количество символов (байт)

// ------------------------------- Структуры --------------------------------------



// Узел дерева Хаффмана
/*
вводим узлы дерева
          (*)
         /   \
       (*)   'A'
      /   \
    'B'   'C'
Узлы 'A', 'B', 'C' — это листья, у которых:
symbol = 'A', is_leaf = 1, left = right = NULL
*/
typedef struct Node {
    unsigned char symbol;    // Символ (если это лист)
    struct Node *left;       // Левый потомок
    struct Node *right;      // Правый потомок
    int is_leaf;             // Флаг: 1 — лист, 0 — внутренний узел
} Node;






// Элемент для построения дерева — пара (узел, частота)
typedef struct {
    Node *node;              // Указатель на узел
    unsigned int freq;       // Частота символа или суммы частот поддеревьев
} Elem;





// Структура для чтения битов из файла
typedef struct {
    FILE *file;              // Файл для чтения
    unsigned char buffer;    // Буфер для битов
    int bits_left;           // Сколько бит осталось в буфере
} BitReader;





// Структура для записи битов в файл
typedef struct {
    FILE *file;              // Файл для записи
    unsigned char buffer;    // Буфер для битов
    int bits_filled;         // Сколько бит записано в буфер
} BitWriter;





// --- Создание узла дерева ---

Node *make_node(void) {
    // Выделение памяти под узел
    Node *node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Out of memory\n"); // stderr —  поток вывода ошибок (standard error)
        exit(1);
    }
    node->left = node->right = NULL;  // Потомки по умолчанию NULL
    node->is_leaf = 0;                // Изначально считаем узел внутренним, если понадобится создать лист (символ), этот флаг можно изменить
    return node;
}





// --- Освобождение памяти дерева ---

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);   // Освобождаем левое поддерево
    free_tree(root->right);  // Освобождаем правое поддерево
    free(root);              // Освобождаем сам узел
}





// --- Функция сравнения для qsort ---
// Сортирует элементы по частоте в порядке возрастания
/*
компаратор, если частота больше последующей 1, иначе -1
*/
static int cmp(const void *a, const void *b) {
    // Указатели a и b приводятся к типу Elem *
    const Elem *ea = a;
    const Elem *eb = b;
    if (ea->freq < eb->freq) return -1;
    if (ea->freq > eb->freq) return 1;
    return 0;
}




// --- Построение дерева Хаффмана по частотам символов ---

Node *build_tree_from_freq(unsigned int freq[]) {
    Elem elems[MAX_SYMBOLS];            // Массив (узел + частота)
    int count = 0;

    // Для каждого символа с ненулевой частотой создаём листовой узел
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (freq[i] > 0) {
            Node *leaf = make_node();
            leaf->symbol = (unsigned char)i;
            leaf->is_leaf = 1;
            elems[count].node = leaf;
            elems[count].freq = freq[i];
            count++;
        }
    }

    // Обработка крайних случаев
    if (count == 0) return NULL;           // Пустой входной файл
    if (count == 1) return elems[0].node;  // Только один символ

    // Построение дерева Хаффмана: объединяем по 2 узла с наименьшей частотой
    // Итеративно объединяем два узла с наименьшими частотами
    while (count > 1) {
        // Сортируем массив по частоте
        qsort(elems, count, sizeof(Elem), cmp);

        // Объединение двух узлов в потомков родителя
        Node *left = elems[0].node;
        Node *right = elems[1].node;

        // Создаём новый внутренний узел
        Node *parent = make_node();     // Новый родительский узел
        parent->left = left;
        parent->right = right;
        parent->is_leaf = 0;

        // Обновляем первый элемент — теперь он родитель с суммарной частотой
        elems[0].node = parent;
        elems[0].freq = elems[0].freq + elems[1].freq;

        // Удаляем второй элемент, заменяя его последним
        elems[1] = elems[count - 1];
        count--;
    }

    // Возвращаем корень дерева
    return elems[0].node;
}





// --- Рекурсивное построение таблицы кодов (для каждого символа код — последовательность бит) ---

typedef struct {
    unsigned int bits;    // Код символа, хранящийся в младших битах
    int length;           // Длина кода в битах
} Code;


void build_codes(Node *node, Code codes[], unsigned int code, int length) {
    if (node->is_leaf) {
        // Если это лист, записываем код для символа
        codes[node->symbol].bits = code;
        codes[node->symbol].length = length;
        return;
    }
    // Спускаемся налево, добавляя 0 к коду (сдвиг влево)
    if (node->left)
        build_codes(node->left, codes, (code << 1), length + 1);
    // Спускаемся направо, добавляя 1 к коду
    if (node->right)
        build_codes(node->right, codes, (code << 1) | 1, length + 1);
}







// --- Инициализация BitWriter (для записи битов в файл) ---

void bw_init(BitWriter *bw, FILE *file) {
    bw->file = file;
    bw->buffer = 0;
    bw->bits_filled = 0;
}


// Запись одного бита в буфер
void bw_write_bit(BitWriter *bw, int bit) {
    bw->buffer = (bw->buffer << 1) | (bit & 1);
    bw->bits_filled++;
    // Как только накопилось 8 бит, пишем байт в файл
    if (bw->bits_filled == 8) {
        fputc(bw->buffer, bw->file);
        bw->bits_filled = 0;
        bw->buffer = 0;
    }
}

// Запись нескольких бит (код символа)
void bw_write_bits(BitWriter *bw, unsigned int bits, int length) {
    // Записываем биты начиная с самого старшего
    for (int i = length - 1; i >= 0; i--) {
        bw_write_bit(bw, (bits >> i) & 1);
    }
}



// Запись остатка (если последний байт заполнен не полностью)
void bw_flush(BitWriter *bw) {
    if (bw->bits_filled > 0) {
        bw->buffer <<= (8 - bw->bits_filled); // сдвигаем, чтобы старшие биты были нулями
        fputc(bw->buffer, bw->file);     
        bw->bits_filled = 0;
        bw->buffer = 0;
    }
}





// --- Инициализация BitReader (для чтения битов из файла) ---

void br_init(BitReader *br, FILE *file) {
    br->file = file;
    br->buffer = 0;
    br->bits_left = 0;
}


// Чтение одного бита из файла
int br_read_bit(BitReader *br) {
    if (br->bits_left == 0) {
        int c = fgetc(br->file);
        if (c == EOF) return -1;  // Конец файла
        br->buffer = (unsigned char)c;
        br->bits_left = 8;
    }
    int bit = (br->buffer >> 7) & 1;  // старший бит буфера
    br->buffer <<= 1;
    br->bits_left--;
    return bit;
}





// --- Запись дерева Хаффмана в файл (в виде битов) ---

void write_tree(Node *node, BitWriter *bw) {
    if (node->is_leaf) {
        bw_write_bit(bw, 1);  // признак листа — 1
        // Записываем символ 8 битами
        for (int i = 7; i >= 0; i--) {
            bw_write_bit(bw, (node->symbol >> i) & 1);
        }
    } else {
        bw_write_bit(bw, 0);  // признак внутреннего узла — 0
        write_tree(node->left, bw);
        write_tree(node->right, bw);
    }
}



// --- Чтение дерева из файла (рекурсивно) ---

Node *read_tree(BitReader *br) {
    int bit = br_read_bit(br);
    if (bit == -1) return NULL; // ошибка или конец файла

    Node *node = make_node();

    if (bit == 1) {
        // лист — читаем символ по 8 бит
        unsigned char sym = 0;
        for (int i = 0; i < 8; i++) {
            int b = br_read_bit(br);
            if (b == -1) {
                free(node);
                return NULL;
            }
            sym = (sym << 1) | b;
        }
        node->symbol = sym;
        node->is_leaf = 1;
    } else {
        // внутренний узел — рекурсивно читаем потомков
        node->is_leaf = 0;
        node->left = read_tree(br);
        node->right = read_tree(br);
    }
    return node;
}



// --- Функция компрессии файла ---

void compress_file(FILE *fin, FILE *fout) {
    unsigned int freq[MAX_SYMBOLS];
    int c;

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        freq[i] = 0;
    }
    
    // Подсчёт частот каждого символа во входном файле
    while ((c = fgetc(fin)) != EOF) {
        freq[(unsigned char)c]++;
    }
    rewind(fin);  // возвращаем указатель в начало файла

    // Строим дерево Хаффмана по частотам символов
    Node *root = build_tree_from_freq(freq);
    if (!root) {
        fprintf(stderr, "Input file is empty\n");
        return;
    }

    // Строим таблицу кодов для всех символов
    Code codes[MAX_SYMBOLS];
    
    for (int i = 0; i < MAX_SYMBOLS; i++) {
    codes[i].bits = 0;
    codes[i].length = 0;
    }

    build_codes(root, codes, 0, 0);

    // Записываем в выходной файл 64-битное число — размер исходного файла в байтах
    fseek(fin, 0, SEEK_END);                //fseek управление положением указателя чтения/записи в открытом файле.
    uint64_t filesize = ftell(fin);         //ftell возвращает текущую позицию указателя чтения/записи в открытом файле.
    fseek(fin, 0, SEEK_SET);
    fwrite(&filesize, sizeof(uint64_t), 1, fout);

    // Инициализируем BitWriter для записи битов
    BitWriter bw;
    bw_init(&bw, fout);

    // Записываем дерево Хаффмана в файл битами
    write_tree(root, &bw);

    // Кодируем и записываем содержимое файла с использованием кодов Хаффмана
    while ((c = fgetc(fin)) != EOF) {
        bw_write_bits(&bw, codes[(unsigned char)c].bits, codes[(unsigned char)c].length);
    }

    // Записываем остаток буфера, если он не пуст
    bw_flush(&bw);

    // Освобождаем память
    free_tree(root);
}

// --- Функция декомпрессии файла ---

void decompress_file(FILE *fin, FILE *fout) {
    uint64_t filesize = 0;

    // Считываем из архива длину исходного файла
    if (fread(&filesize, sizeof(uint64_t), 1, fin) != 1) {
        fprintf(stderr, "Invalid archive format\n");
        return;
    }

    // Инициализируем BitReader для чтения битов
    BitReader br;
    br_init(&br, fin);

    // Считываем дерево Хаффмана из архива
    Node *root = read_tree(&br);
    if (!root) {
        fprintf(stderr, "Invalid tree in archive\n");
        return;
    }

    // Раскодируем данные: для каждого символа идём по дереву от корня до листа по битам
    for (uint64_t i = 0; i < filesize; i++) {
        Node *node = root;
        while (!node->is_leaf) {
            int bit = br_read_bit(&br);
            if (bit == -1) {
                fprintf(stderr, "Unexpected end of file\n");
                free_tree(root);
                return;
            }
            if (bit == 0)
                node = node->left;
            else
                node = node->right;
        }
        fputc(node->symbol, fout);
    }

    free_tree(root);
}






// --- Главная функция, обработка аргументов командной строки ---

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s c input_file output_file  # compress\n", argv[0]);
        fprintf(stderr, "  %s d input_file output_file  # decompress\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[2], "rb");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fout = fopen(argv[3], "wb");
    if (!fout) {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    if (argv[1][0] == 'c') {
        compress_file(fin, fout);
    } else if (argv[1][0] == 'd') {
        decompress_file(fin, fout);
    } else {
        fprintf(stderr, "Unknown command '%s'\n", argv[1]);
        fclose(fin);
        fclose(fout);
        return 1;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
