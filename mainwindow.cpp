#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

string getCapitalLettersWithout(string text)//переписывает все буквы в главные без пробелов

{
    string onlyLettersText = "";
    for (int i = 0; i < text.length(); i++)//с 0 до последней буквы алфавита

    {
        if (text[i] != ' ')
        {
            if (text[i] >= 'a' && text[i] <= 'z')
                onlyLettersText += (text[i] - ('a' - 'A'));//по таблице аскил

            else
                onlyLettersText += (text[i]);
        }
    }
    return onlyLettersText;
}

/*
void getVigenerTable(int size, char** viginerTab)//генерируем таблицу вижинера
{
    char firstLetter = 'A';//начинаем с А

    int i, j;// i сторка, j стобик

    int counter = 0;//счётчик

    // starts with B
    for (i = 0; i < size; i++)
    {
        counter = i + 1;
        for (j = 0; j < size; j++)
        {
            if (counter == size)
                counter = 0;
            viginerTab[i][j] = firstLetter + counter;
            counter++;
        }
        viginerTab[i][j] = '\0';
    }
}


string encryptViegener(string origText, string key)// пишет таблицу вижинера, текст исходный и ключ
{
    int ALF_SIZE = 26;// составление таблицы в соответствии с выбранным языком (количество букв в нем)
    string result = "";
    string onlyLettersText = "";
    string onlyLettersKey = "";
    string keyLenthOfText = "";
    int i, j;
    // char viginerTab[ALF_SIZE][ALF_SIZE];
    char** viginerTab = new char* [ALF_SIZE];
    for (i = 0; i < ALF_SIZE; i++)
        viginerTab[i] = new char[ALF_SIZE];
    char firstLetter = 'A';

    getVigenerTable(ALF_SIZE, viginerTab);
    /*for (i = 0; i < ALF_SIZE; i++)
    {
        cout << i << " ";
        for (j = 0; j < ALF_SIZE; j++)
        {
            cout << viginerTab[i][j];
        }
        cout << endl;
    }

    onlyLettersText = getCapitalLettersWithout(origText);//буквенный тест заменяем на тест большими буквами проработанные таблицой

    //cout << onlyLettersText << endl;
    onlyLettersKey = getCapitalLettersWithout(key);//тоже самое с ключом

    for (i = 0; i < onlyLettersText.length() / onlyLettersKey.length(); i++)
        keyLenthOfText += onlyLettersKey;
    for (i = 0; i < onlyLettersText.length() % onlyLettersKey.length(); i++)
        keyLenthOfText += onlyLettersKey[i];
    // cout << keyLenthOfText << endl;
    int rowNumb = 0;
    int columnNumb = 0;
    int k = 0;
    for (i = 0; i < onlyLettersText.length(); i++)
    {
        for (k = 0; k < ALF_SIZE; k++)
            if (viginerTab[k][0] == keyLenthOfText[i])
                rowNumb = k;
        // cout << "rowNumb = " << rowNumb << endl;//определяется номер строки

        for (k = 0; k < ALF_SIZE; k++)
            if (viginerTab[0][k] == onlyLettersText[i])
                columnNumb = k;
        /// cout << "columnNumb = " << columnNumb << endl;//определяется номер столбца

        result += viginerTab[rowNumb][columnNumb]; //результат = в виде номера строки и столбца
    }
    return result;
}
*/

string decryptViegener(string origText, string key) {
    int ALF_SIZE = 26;
    string result = "";
    string onlyLettersText = getCapitalLettersWithout(origText);
    string onlyLettersKey = getCapitalLettersWithout(key);

    for (int i = 0; i < onlyLettersText.length(); ++i) {
        char keyLetter = onlyLettersKey[i % onlyLettersKey.length()];
        result += (std::abs(onlyLettersText[i] - keyLetter + 1 + ALF_SIZE)) % ALF_SIZE + 'A';
    }

    return result;
}

string encryptViegenerShort(string origText, string key) {
    int ALF_SIZE = 26;
    string result = "";
    string onlyLettersText = getCapitalLettersWithout(origText);
    string onlyLettersKey = getCapitalLettersWithout(key);

    for (int i = 0; i < onlyLettersText.length(); ++i) {
        char keyLetter = onlyLettersKey[i % onlyLettersKey.length()];
        result += (std::abs(onlyLettersText[i] + keyLetter - 1 + ALF_SIZE)) % ALF_SIZE + 'A';
    }

    return result;
}


void MainWindow::on_encryptButton_clicked()
{
    string key = this->ui->keyEdit->text().toStdString();
    string textToEncrypt = this->ui->enteredTextEdit->toPlainText().toStdString();
    this->ui->processedTextEdit->setText(QString::fromStdString(encryptViegenerShort(textToEncrypt, key)));
}


void MainWindow::on_decryptButton_clicked()
{
    string key = this->ui->keyEdit->text().toStdString();
    string textToEncrypt = this->ui->enteredTextEdit->toPlainText().toStdString();
    this->ui->processedTextEdit->setText(QString::fromStdString(decryptViegener(textToEncrypt, key)));
}

