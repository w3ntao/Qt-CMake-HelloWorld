#define PY_SSIZE_T_CLEAN

#include <Python.h>

#include "mainwindow.h"
#include <QApplication>

#include <iostream>

void print_error_info() {
    printf("please run it with `./hello-qt 0`, `./hello-qt 1` or `./hello-qt 2`\n");
}

void execute_python_program(const std::string &filename) {
    wchar_t *program = Py_DecodeLocale("", NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);  // optional but recommended

    Py_Initialize();

    printf("executing `%s`\n", filename.c_str());

    PyObject * obj = Py_BuildValue("s", filename.c_str());
    FILE *fp = _Py_fopen_obj(obj, "r+");
    if (fp == NULL) {
        std::cerr << "file `" << filename << "` not found\n\n";
        exit(1);
    }

    PyRun_SimpleFile(fp, filename.c_str());
    fclose(fp);

    if (Py_FinalizeEx() < 0) {
        exit(-1);
    }

    PyMem_RawFree(program);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_error_info();
        exit(0);
    }

    if (std::string(argv[1]) == "0") {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }

    if (std::string(argv[1]) == "1") {
        execute_python_program("../qdiag-with-qapplication.py");
        return 0;
    }

    if (std::string(argv[1]) == "2") {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        execute_python_program("../qdiag-without-qapplication.py");

        return a.exec();
    }

    print_error_info();
    return 0;
}
