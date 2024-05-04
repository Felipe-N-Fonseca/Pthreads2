## **a)** Implemente uma solução utilizando Mutex e comparece com a anterior. O que mudou? Por quê?

**Resposta:** Comparando com a versão anterior do código, a principal diferença é a adição da inicialização, bloqueio e destruição do mutex (pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy). Isso garante que apenas uma thread por vez tenha acesso à variável sum, evitando condições de corrida.

<hr>

## **b)** No final, entregue no README do repositório uma explicação resumida sobre as diferenças entre os valores atingidos. Quais foram as causas das divergências? Por que elas aconteceram?

**Resposta:** a diferença nos valores de pi atingidos entre a versão sem mutex e a versão com mutex são, a presença de condições de corrida na versão sem mutex pode resultar em valores incorretos de sum, e consequentemente de pi. Isso ocorre porque várias threads podem tentar atualizar sum simultaneamente, causando inconsistências. Com o uso do mutex, garantimos que apenas uma thread por vez atualize sum, garantindo assim um resultado correto.

<hr>

- A resolução está na página da Wiki do repositório, junto do print do mesmo.
