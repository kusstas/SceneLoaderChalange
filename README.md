# SceneLoaderChalange
Критерии выбора : 
1. Сцена с tmx визуально  полностью сконвертилась в qml. 
2. Кликабельные обьекты в tmx , стали кликабельными обьектами в qml 
3. События из tmx хэндлятся в основном приложении (БЕЗ ИЗМЕНЕНИЯ КОДА ОСНОВНОГО ПРИЛОЖЕНИЯ, БЕЗ ЕБУЧИХ БАЙНДИНГОВ), то есть можно менять только файл SceneLoader.qml 4. Поддержка анимаций.    

То есть по сути ожидаются изменения только в файле SceneLoader.qml, в нем может вызыватся библиотека, ок. Но семпл не прикосаем. В папке scenes, ожидается несколько tmx, и какой либо формат ваших файлов для внутриних стейтов, логики переходов итп.  

В итоге все будет выбиратся с точки зрения конечного пользователя. Потому что цель этого модуля в удобном конверте данных из tiled в QML. И посторатся поддержать как можно больше функционала.  А главное, в конце этим будут пользоватся люди без знания QML! они просто выгрузят все в папку и забудут. 


env:
Qt 5.14 support  and highter.
compile on android and linux.
