# Проекты сборки файлов FLM.

Все FLM поддерживают стирание по секторам.

При открытии проектов, отказаться от предложения установить 
"Legacy Support for ARM7, ARM9 & Cortex-R"

"Legacy support for Arm Cortex-M devices" должен быть установлен.

FLM НЕ собираются в демо-версии, ограничение на MDK-Lite.

В директории test лежат тестовые проекты, которые запускаются из ОЗУ и вызывают функции FPL для проверки их работоспособности.


## Особенности для 1986ВЕ4У, 1986ВЕВК214, 1986ВК234
В FLM для 1986ВЕ4У, 1986ВЕВК214, 1986ВК234 при вызове функции EraseAll() проверяется бит FPOR в регистре REG_0E блока BKP. Если бит FPOR равен 0, то в информационную память записывается начальный загрузчик.

Бит FPOR равен нулю при запуске МК после подачи питания. Исполняясь начальный загрузчик выставляет бит FPOR, который не сбрасывается при последующих reset. Таким образом, обычный запуск FLM не приводит к перезаписи начального загрузчика.

Но если начальный загрузчик в информационной памяти будет испорчен, то он не отработает при включении питания и бит FPOR останется равен 0. Вызов стирания Erase в Keil в данной ситуации перезапишет загрузчик когда будет исполняться FLM.