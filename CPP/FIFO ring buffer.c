#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024 

typedef struct {
    uint8_t bytes[BUF_SIZE]; // Массив для хранения данных
    uint16_t idxRead; // текущий индекс чтения
    uint16_t idxWrite; // следующий индекс записи
    uint8_t is_full;   // 0 - не полный, 1 - полный
} RingBuffer;

RingBuffer rb = { .idxRead = 0, .idxWrite = 0, .is_full=0,};

//При переполнении новые байты затирают старые
void AddToBuf(uint8_t len, uint8_t* data)
{
    if (len == 0 || data == NULL) return; //не правильные переданные данные

    for (uint16_t i = 0; i < len; ++i) //если len > BUF_SIZE то перезаписывается весь буфер циклически
    {
        rb.bytes[rb.idxWrite] = data[i];
        rb.idxWrite = (rb.idxWrite + 1) % BUF_SIZE;

        if (rb.is_full) // если был полный то при записи сдвигаем указатель чтения, чтобы перезаписать самые старые данные
        {
            rb.idxRead = (rb.idxRead + 1) % BUF_SIZE;
         } else if (rb.idxWrite == rb.idxRead) { // буфер стал полон
            rb.is_full = 1;
        }
    }

}

//только символы без завершающего \0
void AddToBuf_TextMessage(const char *str_format, ...)
{
    if (str_format == NULL) return;//не правильные переданные данные

    const int STATIC_BUF_SIZE = 256; //максимальный размер который может записать AddToBuf (если больше то текст обрежется)
    char static_buf[STATIC_BUF_SIZE];

    va_list ap;
    va_start(ap, str_format);

    va_list ap_copy;
    va_copy(ap_copy, ap); //чтобы vsnprintf не изменил ap
    size_t n = vsnprintf(static_buf, STATIC_BUF_SIZE, str_format, ap_copy);//определяем число символов без \0
    va_end(ap_copy);

    char *msg_buf = NULL;
    size_t msg_len = 0;

    if (n <= 0) {va_end(ap); return;} //произошла ошибка форматирования

    //Логика выбора буфера для форматированной строки (статический или динамический)
    if (n < STATIC_BUF_SIZE) //Если результат поместился в статический буфер
    {
        msg_buf = static_buf;//как источник данных
        msg_len = n; //число символов без завершающего '\0'

     } else { // иначе нужен больший буфер

        size_t buf_size = n + 1;//Выделяем динамически буфер размера n+1 чтобы вместить завершающий NUL
        msg_buf = (char*)malloc(buf_size);
        if (msg_buf == NULL) {va_end(ap); return;} // Проверка malloc; при OOM завершаем

        n = vsnprintf(msg_buf, buf_size, str_format, ap);//записывание строки в выделенный буфер (первый вызов был только для вычисления кол-во символов)
        if (n <= 0){free(msg_buf); va_end(ap); return;}//произошла ошибка форматирования

        msg_len = n;//длина строки без '\0'
    }

    //Добавление в кольцевой буфер
    if (msg_len > 0) 
    {
        size_t offset = 0;
        //шлём данные в AddToBuf порциями по максимуму 255 байт т.к. AddToBuf принимает uint8_t
        while (msg_len > 0)
        {
            uint8_t chunk = (msg_len > 255) ? 255 : (uint8_t)msg_len;
            AddToBuf(chunk, (uint8_t*)(msg_buf + offset));
            offset += chunk;
            msg_len -= chunk;
        }
    }

    //Очистка и завершение
    if (msg_buf != static_buf) {free(msg_buf);}//Если msg_buf указывает не на static_buf (т.е. выделялась память)
    va_end(ap);
}

//После чтения байт остается но считается использованным (можно перезаписать)
uint8_t GetFromBuf(void)
{
    
    if (!rb.is_full && (rb.idxWrite == rb.idxRead)) {return -1;}// Проверка на пустоту

    uint8_t val = rb.bytes[rb.idxRead];
    rb.idxRead = (rb.idxRead + 1) % BUF_SIZE;

    
    rb.is_full = 0;//После чтения буфер уже не полон

    return val;
}

//функция для теста
//Читаем всё, что есть и печатаем
void Read_TextMessage()
{
    while (rb.is_full || (rb.idxWrite != rb.idxRead)) 
    {
        uint8_t b = GetFromBuf();
        printf("%c", b);
    }
}

int main(void) 
{
    AddToBuf_TextMessage("Hello world!");
    unsigned int number = 23;
    AddToBuf_TextMessage("number = %u \n", number);

    Read_TextMessage();

    const char *str = "In a small cafe on the corner, where students and artists shared mismatched tables, the scent of freshly ground coffee and warm pastries wove through quiet conversations. The old barista moved with practiced gestures, his lined face a map of years spent serving strangers turned regulars. Black-and-white photographs hung on the wall, frozen moments from different eras that seemed to whisper the histories of people who had once found refuge here. Outside, a lone tram clicked along its tracks, its rhythm adding a gentle percussion to the evening. Two friends at the window sketched plans for winter, laughing as they recalled past misadventures and imagined new ones. Time inside the café felt intentionally slow, as if the room itself granted a brief reprieve from the city’s rush. The warmth wasn’t only from tea and blankets but from the quiet knowledge that somewhere, tucked away among ordinary streets, there remained a place where one could simply be, letting thoughts unfurl without hurry.";
    AddToBuf_TextMessage("%s", str);

    Read_TextMessage();

    return 0;
}
