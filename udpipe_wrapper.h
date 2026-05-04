#ifndef UDPIPE_WRAPPER_H
#define UDPIPE_WRAPPER_H

#include "udpipe-master/src_lib_only/udpipe.h" // Se o header estiver na mesma pasta ou no path do -I
#include <string>
#include <sstream>

class UDPipeAnalisador {
public:
    ufal::udpipe::model* m_model;
    ufal::udpipe::pipeline* m_pipeline;

    UDPipeAnalisador(const std::string& modelPath) {
        m_model = ufal::udpipe::model::load(modelPath.c_str());
        if (!m_model) {
            m_pipeline = nullptr;
            return;
        }
        // Configura o pipeline para tokenizer, tagger e parser
        m_pipeline = new ufal::udpipe::pipeline(m_model, "tokenizer", "tagger", "parser", "conllu");
    }

    ~UDPipeAnalisador() {
        if (m_pipeline) delete m_pipeline;
        if (m_model) delete m_model;
    }

    std::string Analisar(const std::string& texto) {
        if (!m_pipeline) return "Erro: Modelo UDPipe nao carregado.";

        std::istringstream input(texto);
        std::ostringstream output;
        std::string error;
        
        bool ok = m_pipeline->process(input, output, error);
        
        if (!ok) return "Erro no processamento: " + error;

        return output.str(); 
    }
};

#endif