# PC com MMU

Repositório de um projeto em C que implementa a simulação de um processador com Unidade de Gerenciamento de Memória (MMU — Memory Management Unit).

## Conteúdo

- **cpu.c**, **cpu.h**: núcleo do processador, responsável por buscar, decodificar e executar instruções.
- **mmu.c**, **mmu.h**: componente que faz a tradução de endereços virtuais para físicos e controla proteção de memória.
- **ramTP.c**, **ramTP.h**: simulação da memória principal (RAM) e possíveis interações com instruções.
- **geradorHD.c**, **geradorHD.h**: geração simulada de "HD" (memória secundária ou armazenamento persistente).
- **gerarInst.c**, **gerarInst.h**: ferramenta para gerar instruções (possivelmente um gerador de programas ou cargas de testes).
- **leituraInstrucao.c**, **leituraInstrucao.h**: leitura e interpretação das instruções geradas ou carregadas.
- **main.c**: programa principal que orquestra a simulação.
- **programa.txt**: possivelmente um exemplo de entrada (programa ou sequência de instruções a ser executado).

## Funcionalidades

- Simulação básica de um processador com pipeline simples ou abordagem básica.
- Tradução de endereços virtuais para físicos via MMU, com proteção de memória.
- Interação entre memória primária (RAM) e secundária (HD simulado).
- Geração e leitura de instruções para testar o comportamento da CPU e da MMU.

## Como executar

### 1. Clonar o repositório

```bash
git clone https://github.com/Caualemoscamara/PC-com-MMU.git
cd PC-com-MMU
```

### 2. Compilar o projeto

Use o `gcc` para compilar todos os arquivos necessários em um executável chamado `simulador`:

```bash
gcc -o simulador main.c cpu.c mmu.c ramTP.c geradorHD.c gerarInst.c leituraInstrucao.c
```

### 3. Executar

```bash
./simulador programa.txt
```

> ⚠️ Ajuste os parâmetros conforme a implementação real ou instruções específicas do projeto.

## Estrutura de pastas

```
PC-com-MMU/
├── cpu.c
├── cpu.h
├── mmu.c
├── mmu.h
├── ramTP.c
├── ramTP.h
├── geradorHD.c
├── geradorHD.h
├── gerarInst.c
├── gerarInst.h
├── leituraInstrucao.c
├── leituraInstrucao.h
├── main.c
└── programa.txt
```

## Como contribuir

- **Issues**: relate bugs ou sugira melhorias.
- **Pull Requests**: contribua com novas funcionalidades como:
  - Logs mais detalhados (estado da MMU, falha de proteção etc.).
  - Suporte a múltiplos processos ou níveis de privilégio.
  - Visualização gráfica da tradução de endereços ou conteúdo da memória.
  - Testes automatizados.

## Licença

Este projeto está licenciado sob a [MIT License](./LICENSE).

## Sobre MMU

A Unidade de Gerenciamento de Memória (MMU) é um hardware essencial que traduz endereços virtuais, usados pelos programas, em endereços físicos — protegendo a memória e permitindo, por exemplo, o uso de memória virtual ([pt.wikipedia.org](https://pt.wikipedia.org/wiki/Unidade_de_gerenciamento_de_mem%C3%B3ria?utm_source=chatgpt.com)).
