#define PY_SSIZE_T_CLEAN

#include <Python.h>

#include "mainwindow.h"
#include <QApplication>

#include <iostream>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::cout << "main window created\n" << std::flush;

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);  /* optional but recommended */

    Py_Initialize();

    std::string filename = "../qdiag.py";
    PyObject *obj = Py_BuildValue("s", filename.c_str());
    FILE *fp = _Py_fopen_obj(obj, "r+");
    if (fp == NULL) {
        std::cerr << "file `" << filename << "` not found\n\n";
        exit(1);
    }

    PyRun_SimpleFile(fp, filename.c_str());
    fclose(fp);

    printf("python script `%s` executed\n", filename.c_str());

    if (Py_FinalizeEx() < 0) {
        exit(120);
    }

    PyMem_RawFree(program);


    return a.exec();
}
