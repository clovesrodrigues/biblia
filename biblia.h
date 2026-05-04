#ifndef BIBLIA_H
#define BIBLIA_H

#include <wx/wx.h>
#include <vector>
#include <map>

// Definições para facilitar a busca (Índices dos Livros)
// Antigo Testamento
#define GENESIS          0
#define EXODO            1
#define LEVITICO         2
#define NUMEROS          3
#define DEUTERONOMIO     4
#define JOSUE            5
#define JUIZES           6
#define RUTE             7
#define SAMUEL1          8
#define SAMUEL2          9
#define REIS1            10
#define REIS2            11
#define CRONICAS1        12
#define CRONICAS2        13
#define ESDRAS           14
#define NEEMIAS          15
#define ESTER            16
#define JO               17
#define SALMOS           18
#define PROVERBIOS       19
#define ECLESIASTES      20
#define CANTARES         21
#define ISAIAS           22
#define JEREMIAS         23
#define LAMENTACOES      24
#define EZEQUIEL         25
#define DANIEL           26
#define OSEIAS           27
#define JOEL             28
#define AMOS             29
#define OBADIAS          30
#define JONAS            31
#define MIQUEIAS         32
#define NAUM             33
#define HABACUQUE        34
#define SOFONIAS         35
#define AGEU             36
#define ZACARIAS         37
#define MALAQUIAS        38

// Novo Testamento
#define MATEUS           39
#define MARCOS           40
#define LUCAS            41
#define JOAO             42
#define ATOS             43
#define ROMANOS          44
#define CORINTIOS1       45
#define CORINTIOS2       46
#define GALATAS          47
#define EFESIOS          48
#define FILIPENSES       49
#define COLOSSENSES      50
#define TESSALONICENSES1 51
#define TESSALONICENSES2 52
#define TIMOTEO1         53
#define TIMOTEO2         54
#define TITO             55
#define FILEMON          56
#define HEBREUS          57
#define TIAGO            58
#define PEDRO1           59
#define PEDRO2           60
#define JOAO1            61
#define JOAO2            62
#define JOAO3            63
#define JUDAS            64
#define APOCALIPSE       65

// Estruturas
struct StructCapitulo {
    std::map<int, wxString> versos; 
};

struct StructLivro {
    wxString nome;
    std::map<int, StructCapitulo> capitulos;
};

// Classe Principal da DLL
class Biblia {
public:
    std::map<int, StructLivro> dados;
    wxString versaoNome;

    void Inicializar() {
        versaoNome = wxT("Almeida Atualizada");

        // Antigo Testamento
        CarregarGenesis(this);
        CarregarExodo(this);
        CarregarLevitico(this);
        CarregarNumeros(this);
        CarregarDeuteronomio(this);
        CarregarJosue(this);
        CarregarJuizes(this);
        CarregarRute(this);
        Carregar1Samuel(this);
        Carregar2Samuel(this);
        Carregar1Reis(this);
        Carregar2Reis(this);
        Carregar1Cronicas(this);
        Carregar2Cronicas(this);
        CarregarEsdras(this);
        CarregarNeemias(this);
        CarregarEster(this);
        CarregarJo(this);
        CarregarSalmos(this);
        CarregarProverbios(this);
        CarregarEclesiastes(this);
        CarregarCantares(this);
        CarregarIsaias(this);
        CarregarJeremias(this);
        CarregarLamentacoes(this);
        CarregarEzequiel(this);
        CarregarDaniel(this);
        CarregarOseias(this);
        CarregarJoel(this);
        CarregarAmos(this);
        CarregarObadias(this);
        CarregarJonas(this);
        CarregarMiqueias(this);
        CarregarNaum(this);
        CarregarHabacuque(this);
        CarregarSofonias(this);
        CarregarAgeu(this);
        CarregarZacarias(this);
        CarregarMalaquias(this);

        // Novo Testamento
        CarregarMateus(this);
        CarregarMarcos(this);
        CarregarLucas(this);
        CarregarJoao(this);
        CarregarAtos(this);
        CarregarRomanos(this);
        Carregar1Corintios(this);
        Carregar2Corintios(this);
        CarregarGalatas(this);
        CarregarEfesios(this);
        CarregarFilipenses(this);
        CarregarColossenses(this);
        Carregar1Tessalonicenses(this);
        Carregar2Tessalonicenses(this);
        Carregar1Timoteo(this);
        Carregar2Timoteo(this);
        CarregarTito(this);
        CarregarFilemon(this);
        CarregarHebreus(this);
        CarregarTiago(this);
        Carregar1Pedro(this);
        Carregar2Pedro(this);
        Carregar1Joao(this);
        Carregar2Joao(this);
        Carregar3Joao(this);
        CarregarJudas(this);
        CarregarApocalipse(this);
    }

    wxString ObterVerso(int livro, int cap, int verso) {
        return dados[livro].capitulos[cap].versos[verso];
    }

    // Declarações das funções de carregamento (uma para cada livro)
    void CarregarGenesis(Biblia* b);
    void CarregarExodo(Biblia* b);
    void CarregarLevitico(Biblia* b);
    void CarregarNumeros(Biblia* b);
    void CarregarDeuteronomio(Biblia* b);
    void CarregarJosue(Biblia* b);
    void CarregarJuizes(Biblia* b);
    void CarregarRute(Biblia* b);
    void Carregar1Samuel(Biblia* b);
    void Carregar2Samuel(Biblia* b);
    void Carregar1Reis(Biblia* b);
    void Carregar2Reis(Biblia* b);
    void Carregar1Cronicas(Biblia* b);
    void Carregar2Cronicas(Biblia* b);
    void CarregarEsdras(Biblia* b);
    void CarregarNeemias(Biblia* b);
    void CarregarEster(Biblia* b);
    void CarregarJo(Biblia* b);
    void CarregarSalmos(Biblia* b);
    void CarregarProverbios(Biblia* b);
    void CarregarEclesiastes(Biblia* b);
    void CarregarCantares(Biblia* b);
    void CarregarIsaias(Biblia* b);
    void CarregarJeremias(Biblia* b);
    void CarregarLamentacoes(Biblia* b);
    void CarregarEzequiel(Biblia* b);
    void CarregarDaniel(Biblia* b);
    void CarregarOseias(Biblia* b);
    void CarregarJoel(Biblia* b);
    void CarregarAmos(Biblia* b);
    void CarregarObadias(Biblia* b);
    void CarregarJonas(Biblia* b);
    void CarregarMiqueias(Biblia* b);
    void CarregarNaum(Biblia* b);
    void CarregarHabacuque(Biblia* b);
    void CarregarSofonias(Biblia* b);
    void CarregarAgeu(Biblia* b);
    void CarregarZacarias(Biblia* b);
    void CarregarMalaquias(Biblia* b);
    void CarregarMateus(Biblia* b);
    void CarregarMarcos(Biblia* b);
    void CarregarLucas(Biblia* b);
    void CarregarJoao(Biblia* b);
    void CarregarAtos(Biblia* b);
    void CarregarRomanos(Biblia* b);
    void Carregar1Corintios(Biblia* b);
    void Carregar2Corintios(Biblia* b);
    void CarregarGalatas(Biblia* b);
    void CarregarEfesios(Biblia* b);
    void CarregarFilipenses(Biblia* b);
    void CarregarColossenses(Biblia* b);
    void Carregar1Tessalonicenses(Biblia* b);
    void Carregar2Tessalonicenses(Biblia* b);
    void Carregar1Timoteo(Biblia* b);
    void Carregar2Timoteo(Biblia* b);
    void CarregarTito(Biblia* b);
    void CarregarFilemon(Biblia* b);
    void CarregarHebreus(Biblia* b);
    void CarregarTiago(Biblia* b);
    void Carregar1Pedro(Biblia* b);
    void Carregar2Pedro(Biblia* b);
    void Carregar1Joao(Biblia* b);
    void Carregar2Joao(Biblia* b);
    void Carregar3Joao(Biblia* b);
    void CarregarJudas(Biblia* b);
    void CarregarApocalipse(Biblia* b);
};

#endif