#include <wx/wx.h>
#include <wx/statline.h>
#include <wx/sysopt.h> 
#include "biblia.h"
#include "udpipe_wrapper.h"
#include <wx/icon.h>

class MeuFrame : public wxFrame {
public:

    MeuFrame() : wxFrame(NULL, wxID_ANY, wxString::FromUTF8("            BIBLIA E CLASSES GRAMATICÁIS - por Cloves Rodrigues            "), wxDefaultPosition, wxSize(800, 600)) {
        minhaBiblia = new Biblia();
        minhaBiblia->Inicializar();

        // Inicializa o UDPipe (certifique-se de que o arquivo .udpipe está na mesma pasta do .exe)
        analisador = new UDPipeAnalisador("portuguese-bosque-ud-2.5-191206.udpipe");

        wxPanel* panel = new wxPanel(this);
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* comboSizer = new wxBoxSizer(wxHORIZONTAL);

        comboLivro = new wxComboBox(panel, wxID_ANY, "Selecione o Livro", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
        comboCapitulo = new wxComboBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
        comboVerso = new wxComboBox(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);

        comboSizer->Add(new wxStaticText(panel, wxID_ANY, "Livro:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        comboSizer->Add(comboLivro, 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        comboSizer->Add(new wxStaticText(panel, wxID_ANY, "Cap:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        comboSizer->Add(comboCapitulo, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        comboSizer->Add(new wxStaticText(panel, wxID_ANY, "Ver:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        comboSizer->Add(comboVerso, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

        // Caixa de texto para o versículo puro
        resultadoTxt = new wxTextCtrl(panel, wxID_ANY, wxString::FromUTF8("      __________      SELECIONE UM VERSÍCULO      __________      "), 
            wxDefaultPosition, wxSize(-1, 100), wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
        
        resultadoTxt->SetBackgroundColour(wxColour(245, 245, 245));
        resultadoTxt->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        // Caixa de texto para a saída do UDPipe
        resultadoLematizadoTxt = new wxTextCtrl(panel, wxID_ANY, "  ----   ANALISE SINTATICA - TODAS AS CLASSES GRAMATICAIS APARECERÃO AQUI :  ----   ", 
            wxDefaultPosition, wxSize(-1, 250), wxTE_MULTILINE | wxTE_READONLY);
        resultadoLematizadoTxt->SetFont(wxFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

        mainSizer->Add(comboSizer, 0, wxEXPAND | wxALL, 10);
        mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 10); 
        mainSizer->Add(resultadoTxt, 0, wxEXPAND | wxALL, 10);
        mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxLEFT | wxRIGHT, 10); 
        mainSizer->Add(resultadoLematizadoTxt, 1, wxEXPAND | wxALL, 10);

        panel->SetSizer(mainSizer);

        for (int i = 0; i <= 65; ++i) {
            wxString nomeLivro = wxString::FromUTF8(minhaBiblia->dados[i].nome.c_str());
            if (nomeLivro.IsEmpty()) nomeLivro = wxString::Format("Livro %d", i+1);
            comboLivro->Append(nomeLivro);
        }

        comboLivro->Bind(wxEVT_COMBOBOX, &MeuFrame::OnLivroSelected, this);
        comboCapitulo->Bind(wxEVT_COMBOBOX, &MeuFrame::OnCapituloSelected, this);
        comboVerso->Bind(wxEVT_COMBOBOX, &MeuFrame::OnVersoSelected, this);
        
        this->Centre();
    }

    ~MeuFrame() {
        delete analisador; // Limpa a memória quando a janela fechar
    }

private:
    // O SEGREDO ESTÁ AQUI: Todas as variáveis precisam ser declaradas na seção private
    Biblia* minhaBiblia;
    UDPipeAnalisador* analisador;        // Agora OnVersoSelected enxerga isso
    wxTextCtrl* resultadoLematizadoTxt;  // Agora OnVersoSelected enxerga isso
    wxTextCtrl* resultadoTxt;
    wxComboBox *comboLivro, *comboCapitulo, *comboVerso;

    void OnLivroSelected(wxCommandEvent& event) {
        int livroIdx = comboLivro->GetSelection();
        comboCapitulo->Clear();
        comboVerso->Clear();
        if (livroIdx != wxNOT_FOUND) {
            auto& caps = minhaBiblia->dados[livroIdx].capitulos;
            for (auto const& [num, cap] : caps) {
                comboCapitulo->Append(wxString::Format("%d", num));
            }
        }
    }

    void OnCapituloSelected(wxCommandEvent& event) {
        int livroIdx = comboLivro->GetSelection();
        long capNum;
        if (comboCapitulo->GetValue().ToLong(&capNum) && livroIdx != wxNOT_FOUND) {
            comboVerso->Clear();
            auto& versos = minhaBiblia->dados[livroIdx].capitulos[(int)capNum].versos;
            for (auto const& [num, texto] : versos) {
                comboVerso->Append(wxString::Format("%d", num));
            }
        }
    }

    void OnVersoSelected(wxCommandEvent& event) {
        int livroIdx = comboLivro->GetSelection();
        long capNum, versoNum;
        
        if (comboCapitulo->GetValue().ToLong(&capNum) && comboVerso->GetValue().ToLong(&versoNum)) {
            // 1. Pega o texto bruto do objeto
            const char* textoBruto = minhaBiblia->dados[livroIdx].capitulos[(int)capNum].versos[(int)versoNum].c_str();
            
            // 2. Tenta converter de UTF-8
            wxString texto = wxString::FromUTF8(textoBruto);
            
            // 3. Se falhar (ficar vazio), tenta converter usando o charset local (Windows)
            if (texto.IsEmpty() && textoBruto[0] != '\0') {
                texto = wxString(textoBruto, wxConvLocal);
            }
    
            wxString ref = wxString::Format("%s %ld:%ld\n\n", comboLivro->GetStringSelection(), capNum, versoNum);
            resultadoTxt->SetValue(ref + texto);
    
            if (analisador) {
                // O UDPipe prefere UTF-8 puro
                std::string analise = analisador->Analisar(texto.ToStdString(wxConvUTF8));
                resultadoLematizadoTxt->SetValue(wxString::FromUTF8(analise.c_str()));
            }
        }
    }
};

class MinhaApp : public wxApp {
public:
    virtual bool OnInit() {
        // Desativa o warning do Manifest
        wxSystemOptions::SetOption("msw.no-manifest-check", 1);
        
        // Garante a acentuação correta
        wxLocale* locale = new wxLocale(wxLANGUAGE_PORTUGUESE);
        
        MeuFrame* frame = new MeuFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MinhaApp);