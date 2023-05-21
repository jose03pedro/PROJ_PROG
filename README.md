## Funções Disponíveis

Aqui estão as funções implementadas neste projeto:

### `fill()`

Preenche uma área retangular dentro da imagem com uma cor especificada. Ela recebe as coordenadas do canto superior esquerdo (x, y), largura (w), altura (h) e cor de preenchimento. Verifica se o retângulo especificado está dentro dos limites da imagem e, em seguida, itera sobre os pixels dentro do retângulo e define sua cor como a cor de preenchimento.

### `invert()`

Inverte a cor na imagem. Ela itera sobre cada pixel na imagem e modifica sua cor subtraindo os valores individuais das cores (vermelho, verde, azul) de 255.

### `to_gray_scale()`

Converte a imagem armazenada no objeto para escala de cinza. Ela itera sobre cada pixel na imagem e calcula o valor médio dos canais de cor vermelho, verde e azul. Em seguida, define a cor de cada pixel como o valor médio calculado para todos os canais de cor, resultando em uma imagem em escala de cinza.

### `replace()`

Substitui todas as ocorrências de uma cor antiga por uma nova cor na imagem. Ela recebe as cores antiga e nova como entrada. Itera sobre cada pixel na imagem e compara sua cor com a cor antiga usando a função compareColors. Se houver correspondência, substitui a cor do pixel pela nova cor.

### `h_mirror()`

Espelha a imagem horizontalmente. Ela itera sobre cada pixel na metade esquerda da imagem e troca sua cor com o pixel correspondente na metade direita da imagem, efetivamente invertendo a imagem horizontalmente.

### `v_mirror()`

Espelha a imagem verticalmente. Ela itera sobre cada pixel na metade superior da imagem e troca sua cor com o pixel correspondente na metade inferior da imagem, efetivamente invertendo a imagem verticalmente.

### `add()`

Sobrepõe a imagem carregada na imagem atual em uma posição especificada, com uma cor especificada. Carrega uma imagem de um arquivo PNG especificado pelo nome do arquivo e verifica se a imagem foi carregada com sucesso. Em seguida, recebe as cores "neutra" (r, g, b) e a posição (x, y) para colocar a imagem carregada. Itera sobre cada pixel na imagem carregada, ignora os pixels que correspondem à cor "neutra" e copia os pixels não neutros para a posição correspondente na imagem atual.

### `crop()`

Cria uma nova imagem cortando uma área retangular da imagem atual. Recebe as coordenadas do canto superior esquerdo (x, y), largura (w) e altura (h) da área de corte. Cria uma nova imagem com as dimensões especificadas e itera sobre os pixels na área de corte, copiando suas cores para a posição correspondente na nova imagem.

### `rotate_left()`

Cria uma nova imagem girando a imagem atual 90 graus no sentido anti-horário. Cria uma nova imagem com dimensões trocadas e itera sobre cada pixel na imagem atual, atribuindo sua cor à posição correspondente na nova imagem, mas com as coordenadas trocadas de acordo com a rotação.

### `rotate_right()`

Cria uma nova imagem girando a imagem atual 90 graus no sentido horário. Cria uma nova imagem com dimensões trocadas e itera sobre cada pixel na imagem atual, atribuindo sua cor à posição correspondente na nova imagem, mas com as coordenadas trocadas de acordo com a rotação.
