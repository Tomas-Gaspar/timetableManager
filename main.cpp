#include <iostream>
#include "GestaoHor.h"
#include <fstream>

using namespace std;

GestaoHor gestao = GestaoHor();

void ocupacaoDeterminadaTurma(){
    /*
     * MEANINGLESS??
     * apenas interessa saber a ocupaçao de uma determinada turma numa uc
     * ja que uma turma tem pessoas diferentes em diferentes ucs
     */
}

void ocupacaoTurmasAno(){
    /*
     * SAME AS ABOVE
     */
    //NAO USAR OCUPACAO DETERMINADATURMA AQUI DENTRO
    //VECTORS<Pair>
}

void ocupacaoTurmas(){
    /*
     * SAME AS ABOVE
     */
}

bool ocupacaoTurmasMenu(){
    while (true) {
        cout << "-> OCUPAÇÃO\n\n";
        cout << "\t-> Turmas\n";
        cout << "\t\t 1 - Determinada Turma\n";
        cout << "\t\t 2 - Turmas de um determinado ano\n";
        cout << "\t\t 3 - Todas as turmas\n";

        cout << "\ntype 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option;
        getline(cin, option);
        if (option == "1") ocupacaoDeterminadaTurma();
        else if (option == "2") ocupacaoTurmasAno();
        else if (option == "3") ocupacaoTurmas();
        else if (option == "q") return true;
        else if (option == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
}

void ocupacaoDeterminadoAno(){
    //TODO
    // como identificar quem pertence a um determinado ano?
    // um aluno pode pertencer a mais que um ano? (acho que sim)
}

void ocupacaoAnos(){
    //TODO
    //SAME AS ABOVE
}

bool ocupacaoAnosMenu(){
    while (true) {
        cout << "-> OCUPAÇÃO\n\n";
        cout << "\t-> Anos\n";
        cout << "\t\t 1 - Determinado Ano\n";
        cout << "\t\t 2 - Todos os Anos\n";

        cout << "\ntype 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option;
        getline(cin, option);
        if (option == "1") ocupacaoDeterminadoAno();
        else if (option == "2") ocupacaoAnos();
        else if (option == "q") return true;
        else if (option == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
}

void ocupacaoDeterminadaUC(string codUC) {
    int ocupacao = 0;
    for (Estudante e: gestao.getStudents()){
        for (UCTurma t: e.getTurmas()){
            if (t.getCodUc() == codUC){
                ocupacao++;
                break;
            }
        }
    }
    if (ocupacao == 0){
        cout << "UC not found\n";
        return;
    }
    cout << codUC << ": " << ocupacao << " alunos\n";
}

void ocupacaoUCsAno(string ano) {
    //TODO
    // ver como saber que ucs pertencem a cada ano
}

void ocupacaoUCs() {
    //TODO
}

bool ocupacaoUCMenu(){
    while (true) {
        cout << "-> OCUPAÇÃO\n\n";
        cout << "\t-> Unidades Curriculares\n";
        cout << "\t\t 1 - Determinada Unidade Curricular\n";
        cout << "\t\t 2 - Unidades Curriculares de um determinado ano\n";
        cout << "\t\t 3 - Todas as Unidades Curriculares\n";

        cout << "\ntype 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option1, option2;
        getline(cin, option1);
        if (option1 == "1") {
            cout << "Código UC: ";
            getline(cin, option2);
            ocupacaoDeterminadaUC(option2);
        }
        else if (option1 == "2") {
            cout << "Ano: ";
            getline(cin, option2);
            ocupacaoUCsAno(option2);
        }
        else if (option1 == "3") ocupacaoUCs();
        else if (option1 == "q") return true;
        else if (option1 == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
}

bool ocupacaoMenu(){
    bool exit = false;
    while (!exit) {
        cout << "-> OCUPAÇÃO\n\n";
        cout << "\t1 - Turmas\n";
        cout << "\t2 - Anos\n";
        cout << "\t3 - Unidades Curriculares\n";

        cout << "\ntype 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option;
        getline(cin, option);
        if (option == "1") exit = ocupacaoTurmasMenu();
        else if (option == "2") exit = ocupacaoAnosMenu();
        else if (option == "3") exit = ocupacaoUCMenu();
        else if (option == "q") return true;
        else if (option == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
    return true;
}

void printHorario(Estudante student){
    string s = "../" + student.getName() + "_horario.txt";
    ofstream out(s);
    for (UCTurma turma : student.getTurmas()){
        cout << "UC: " << turma.getCodUc() << " | Turma: " << turma.getCodTurma() << endl;
        out << "UC: " << turma.getCodUc() << " | Turma: " << turma.getCodTurma() << endl;
        for (Aula aula : turma.getTimetable()){
            cout << '\t' << aula.getWeekday();
            cout << ' ' << aula.getStartHour();
            cout << ' ' << aula.getDuration();
            cout << ' ' << aula.getType() << '\n';
            out << '\t' << aula.getWeekday();
            out << ' ' << aula.getStartHour();
            out << ' ' << aula.getDuration();
            out << ' ' << aula.getType() << '\n';
        }
    }
    cout << '\n';
    out.close();
}

void searchHorarioByNum(){
    string num;
    cout << "Número de Estudante: ";
    getline(cin, num);
    Estudante temp = Estudante();
    auto student = gestao.getStudents().find(temp);
    if (student == gestao.getStudents().end()){
        cout << "Student not found\n";
    }
    else{
        printHorario(*student);
    }
}

void searchHorarioByName(){
    string name;
    cout << "Nome do Estudante: ";
    getline(cin, name);
    for (Estudante student : gestao.getStudents()){
        if (student.getName() == name){
            printHorario(student);
            break;
        }
    }
    cout << "Student not found\n";
}

bool horarioMenu(){
    while (true) {
        cout << "-> HORÁRIO\n\n";
        cout << "\t1 - Pesquisa por número de estudante (recomendado)\n";
        cout << "\t2 - Pesquisa por nome\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option;
        getline(cin, option);
        if (option == "1") searchHorarioByNum();
        else if (option == "2") searchHorarioByName();
        else if (option == "q") return true;
        else if (option == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
}

void estudantesTurma() {
    /*
     * INFORMAÇÃO INUTIL JA QUE AS TURMAS PODEM SER DIFERENTES PARA UCs DIFERENTES
     * MUDAR PARA estudantesTurmaUC
     */
}

void estudantesAno(string ano) {
    if (ano.size() != 1){
        cout << "invalid input\n";
        return;
    }
    bool found = false;
    for (Estudante e: gestao.getStudents()){
        for (UCTurma t: e.getTurmas()){
            if (t.getCodTurma()[0] == ano[0]){
                found = true;
                cout << e.getCode() << " - " << e.getName() << endl;
                break;
            }
        }
    }
    if (!found) cout << "No students found\n";
}

void estudantesUC(string codUC) {
    bool found = false;
    for (Estudante e: gestao.getStudents()){
        for (UCTurma t: e.getTurmas()){
            if (t.getCodUc() == codUC){
                found = true;
                cout << e.getCode() << " - " << e.getName() << endl;
                break;
            }
        }
    }
    if (!found) cout << "No students found\n";
}

bool estudantesMenu(){
    while (true) {
        cout << "-> ESTUDANTES\n\n";
        cout << "\t1 - Estudantes em determinada turma\n";
        cout << "\t2 - Estudantes em determinado ano\n";
        cout << "\t3 - estudantes em determinada UC\n";

        cout << "\n type 'q' to quit, 'r' to return\n";
        cout << "==================================================\n";

        string option1, option2;
        getline(cin, option1);
        if (option1 == "1") estudantesTurma();
        else if (option1 == "2") {
            cout << "Ano: ";
            getline(cin, option2);
            estudantesAno(option2);
        }
        else if (option1 == "3"){
            cout << "Código UC: ";
            getline(cin, option2);
            estudantesUC(option2);
        }
        else if (option1 == "q") return true;
        else if (option1 == "r") return false;
        else {
            cout << "invalid input\n\n";
        }
    }
}

int main() {
    gestao.getDataStudent("../students_classes.csv", "../classes.csv");
    bool exit = false;
    string option;
    while (!exit){
        cout << "====================VISUALIZAR====================\n";
        cout << "1 - OCUPAÇÃO\n";
        cout << "2 - HORÁRIO\n";
        cout << "3 - ESTUDANTES\n";

        cout << "\n type 'q' to quit\n";
        cout << "==================================================\n";

        getline(cin, option);
        if (option == "1") exit = ocupacaoMenu();
        else if (option == "2") exit = horarioMenu();
        else if (option == "3") exit = estudantesMenu();
        else if (option == "q") break;
        else cout <<"invalid input\n\n";
    }
    /*
    list<UCTurma> turmas = gestao.getDataAula("../classes.csv");
    for (UCTurma uc: turmas){
        cout << uc.getCodUc() << '|' << uc.getCodTurma() << '\n';
        for (Aula a: uc.getTimetable()){
            cout << '\t' << a.getWeekday();
            cout << ' ' << a.getStartHour();
            cout << ' ' << a.getDuration();
            cout << ' ' << a.getType() << '\n';
        }
    }

    cout << "----------------------------------------------------\n----------------------------------------------------\n";

    gestao.getDataStudent("../students_classes.csv","../classes.csv");
    for (Estudante e : gestao.getStudents()) {
        cout << e.getName() << '\n';
        for (UCTurma turma : e.getTurmas()){
            cout << turma.getCodUc() << " -- " << turma.getCodTurma() << '\n';
            for (Aula a : turma.getTimetable()){
                cout << '\t' << a.getWeekday();
                cout << ' ' << a.getStartHour();
                cout << ' ' << a.getDuration();
                cout << ' ' << a.getType() << '\n';
            }
        }
    }
     */
    return 0;
}
