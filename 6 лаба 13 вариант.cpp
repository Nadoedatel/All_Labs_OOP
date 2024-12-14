#include <string>
#include <stack>
#include <memory>
#include <fstream>
#include <iostream>
using namespace std;
// Базовый интерфейс для всех команд
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// Класс для хранения текущего состояния текста и буфера обмена
class TextProcessor {
private:
    string text;
    string clipboard;

public:
    TextProcessor(const string& initialText) : text(initialText) {}

    const string& getText() const { return text; }
    const string& getClipboard() const { return clipboard; }

    void setClipboard(const string& newClipboard) { clipboard = newClipboard; }

    void copy(int idx1, int idx2) {
        if (idx1 < idx2 && idx1 >= 0 && idx2 <= text.size()) {
            clipboard = text.substr(idx1, idx2 - idx1);
        }
    }

    void paste(int idx) {
        if (idx >= 0 && idx <= text.size()) {
            text.insert(idx, clipboard);
        }
    }

    void insert(const string& str, int idx) {
        if (idx >= 0 && idx <= text.size()) {
            text.insert(idx, str);
        }
    }

    void deleteText(int idx1, int idx2) {
        if (idx1 < idx2 && idx1 >= 0 && idx2 <= text.size()) {
            text.erase(idx1, idx2 - idx1);
        }
    }
};

// Команда копирования
class CopyCommand : public Command {
private:
    TextProcessor& processor;
    int idx1, idx2;

public:
    CopyCommand(TextProcessor& processor, int idx1, int idx2)
        : processor(processor), idx1(idx1), idx2(idx2) {}

    void execute() override {
        processor.copy(idx1, idx2);
    }

    void undo() override {
        // Для команды Copy нет необходимости в undo
    }
};

// Команда вставки
class PasteCommand : public Command {
private:
    TextProcessor& processor;
    int idx;

public:
    PasteCommand(TextProcessor& processor, int idx) : processor(processor), idx(idx) {}

    void execute() override {
        processor.paste(idx);
    }

    void undo() override {
        // Для упрощения считаем, что вставку можно отменить, удаляя добавленный текст
        processor.deleteText(idx, idx + processor.getClipboard().size());
    }
};

// Команда вставки строки
class InsertCommand : public Command {
private:
    TextProcessor& processor;
    string str;
    int idx;

public:
    InsertCommand(TextProcessor& processor, const string& str, int idx)
        : processor(processor), str(str), idx(idx) {}

    void execute() override {
        processor.insert(str, idx);
    }

    void undo() override {
        processor.deleteText(idx, idx + str.size());
    }
};

// Команда удаления
class DeleteCommand : public Command {
private:
    TextProcessor& processor;
    string deletedText;
    int idx1, idx2;

public:
    DeleteCommand(TextProcessor& processor, int idx1, int idx2)
        : processor(processor), idx1(idx1), idx2(idx2) {}

    void execute() override {
        deletedText = processor.getText().substr(idx1, idx2 - idx1);
        processor.deleteText(idx1, idx2);
    }

    void undo() override {
        processor.insert(deletedText, idx1);
    }
};

// Класс для управления выполнением команд и поддержкой undo/redo
class CommandExecutor {
private:
    TextProcessor& processor;
    stack<unique_ptr<Command>> history;
    stack<unique_ptr<Command>> redoStack;

public:
    CommandExecutor(TextProcessor& processor) : processor(processor) {}

    void executeCommand(unique_ptr<Command> command) {
        command->execute();
        history.push(move(command));
        while (!redoStack.empty()) redoStack.pop(); // Очистить стек для redo при новой команде
    }

    void undo() {
        if (!history.empty()) {
            unique_ptr<Command> command = move(history.top());
            command->undo();
            history.pop();
            redoStack.push(move(command));
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            unique_ptr<Command> command = move(redoStack.top());
            command->execute();
            redoStack.pop();
            history.push(move(command));
        }
    }
};

// Основная функция для демонстрации
int main() {
    TextProcessor processor("Hello World");
    CommandExecutor executor(processor);

    cout << "Inicilizatia text: " << processor.getText() << endl;

    executor.executeCommand(make_unique<CopyCommand>(processor, 0, 5));
    executor.executeCommand(make_unique<PasteCommand>(processor, 11));
    cout << "Posle copy-paste: " << processor.getText() << endl;

    executor.executeCommand(make_unique<InsertCommand>(processor, "Awesome ", 6));
    cout << "Posle insert: " << processor.getText() << endl;

    executor.undo();
    cout << "Posle undo: " << processor.getText() << endl;

    executor.redo();
    cout << "Posle redo: " << processor.getText() << endl;

    return 0;
}
