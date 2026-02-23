%# Ray Tracer CPU — Plano de Desenvolvimento

## Objetivo

Construir um ray tracer CPU em C++ puro, passo a passo, para aprender:
- Álgebra linear aplicada (vetores, produto escalar, normalização)
- Interseções geométricas (raio–esfera, raio–plano)
- Modelo de iluminação (Phong)
- Pipeline de rendering conceptual
- Pensamento físico da luz (sombras, reflexão)

**Output:** imagens em formato PPM (texto puro, zero dependências)
**Build:** Makefile simples com g++

---

## Etapas

### Etapa 0 — Setup do Projeto ✅
- Criar estrutura de pastas: `src/`, `include/`, `output/`
- Criar `Makefile` com regras para compilar e limpar
- Criar `main.cpp` com "Hello, Ray Tracer!" — garantir que compila e corre

---

### Etapa 1 — Classe `Vec3` (Álgebra Linear Fundamental)

**Teoria:**
- Vetor 3D: `(x, y, z)`
- Operações: soma, subtração, multiplicação por escalar
- Produto escalar: `a·b = ax*bx + ay*by + az*bz`
- Produto vetorial: `a×b`
- Comprimento: `||v|| = sqrt(vx² + vy² + vz²)`
- Normalização: `v̂ = v / ||v||`

**Tarefas:**
- [ ] Criar `include/Vec3.h` com struct `Vec3`
- [ ] Implementar operadores (`+`, `-`, `*`, `/`), `dot()`, `cross()`, `length()`, `normalized()`
- [ ] Testar no `main.cpp` (ex: normalizar (3,4,0) → (0.6, 0.8, 0))

---

### Etapa 2 — Classe `Ray` (O Raio de Luz)

**Teoria:**
- Um raio: `P(t) = origin + t * direction`, onde `t ≥ 0`
- `origin` = ponto de partida, `direction` = vetor normalizado

**Tarefas:**
- [ ] Criar `include/Ray.h` com `origin` e `direction`
- [ ] Método `at(double t)` que retorna o ponto ao longo do raio

---

### Etapa 3 — Gerar uma Imagem (Output PPM)

**Teoria:**
- Formato PPM: cabeçalho `P3 width height 255`, depois RGB por pixel, linha a linha
- É texto puro, abre em qualquer viewer de imagens

**Tarefas:**
- [ ] Criar função que escreve um ficheiro `.ppm` a partir de um buffer de cores
- [ ] Gerar gradiente simples (azul→branco) — primeira imagem visível!

---

### Etapa 4 — Câmara e Loop de Rendering

**Teoria:**
- A câmara define um "viewport" (retângulo no espaço 3D)
- Para cada pixel `(i,j)`, calcular coordenadas UV no viewport e lançar um raio
- Função `ray_color(Ray)` retorna a cor para cada raio

**Tarefas:**
- [ ] Criar struct `Camera` com `origin`, `viewport_width`, `viewport_height`, `focal_length`
- [ ] Loop duplo (linhas × colunas): lançar raio por pixel
- [ ] `ray_color()` retorna gradiente do céu por agora

---

### Etapa 5 — Interseção Raio–Esfera

**Teoria:**
- Substituir `P(t)` na equação da esfera `||P - C||² = r²`
- Resulta em equação quadrática: `at² + bt + c = 0`
- Discriminante `Δ = b² - 4ac`:
  - `Δ < 0` → sem interseção
  - `Δ = 0` → 1 ponto (tangente)
  - `Δ > 0` → 2 pontos (entra e sai)

**Tarefas:**
- [ ] Criar `include/Sphere.h` com `center`, `radius`
- [ ] Implementar `hit(Ray, t_min, t_max) → HitRecord`
- [ ] Colorir a esfera com base na normal (mapear n̂ → RGB)
- [ ] Primeira esfera visível!

---

### Etapa 6 — Múltiplos Objetos e Abstração

**Teoria:**
- Polimorfismo: classe base `Hittable` com método virtual `hit()`
- `HittableList`: vetor de objetos, encontrar interseção mais próxima (menor `t`)

**Tarefas:**
- [ ] Criar classe base `Hittable` com `hit()` virtual
- [ ] `Sphere` herda de `Hittable`
- [ ] Criar `HittableList` que itera por todos os objetos
- [ ] Testar com 2–3 esferas

---

### Etapa 7 — Interseção Raio–Plano

**Teoria:**
- Plano definido por ponto `Q` e normal `n̂`
- Interseção: `t = ((Q - O) · n̂) / (D · n̂)`
- Se denominador ≈ 0, raio é paralelo ao plano

**Tarefas:**
- [ ] Criar `include/Plane.h` herdando de `Hittable`
- [ ] Implementar `hit()` com a fórmula
- [ ] Adicionar plano-chão à cena

---

### Etapa 8 — Modelo de Iluminação de Phong

**Teoria:**
- 3 componentes:
  - **Ambiente:** luz mínima constante
  - **Difusa:** `max(0, n̂ · l̂)` — superfícies voltadas para a luz são mais brilhantes
  - **Especular:** `(r̂ · v̂)^α` — brilho concentrado ("highlight")

**Tarefas:**
- [ ] Criar `include/Light.h` com `position` e `intensity`
- [ ] Implementar `phong_shade(HitRecord, Light, Camera)`
- [ ] Atribuir propriedades de material (`ambient`, `diffuse`, `specular`, `shininess`)
- [ ] Esferas com aspeto 3D convincente!

---

### Etapa 9 — Sombras

**Teoria:**
- Lançar **shadow ray** do ponto de interseção em direção à luz
- Se atingir outro objeto antes da luz → ponto na sombra (só luz ambiente)
- Usar `ε` (bias) para evitar "shadow acne" (auto-interseção por imprecisão numérica)

**Tarefas:**
- [ ] Para cada ponto, lançar raio para a luz
- [ ] Se houver interseção antes da luz → apenas componente ambiente
- [ ] Implementar epsilon bias

---

### Etapa 10 — Reflexão

**Teoria:**
- Direção refletida: `r̂ = d̂ - 2(d̂ · n̂)n̂`
- Para superfícies refletoras, lançar novo raio na direção refletida
- Processo **recursivo** — precisa de limite de profundidade (`max_depth`)

**Tarefas:**
- [ ] Adicionar `reflectivity` (0.0–1.0) ao material
- [ ] Implementar reflexão recursiva em `ray_color()` com `max_depth`
- [ ] Testar com esfera espelhada — momento "wow"!

---

### Etapa 11 — Cena Final e Polish

**Tarefas:**
- [ ] Compor cena: plano-chão, 3–5 esferas (mate, brilhante, espelhada), 1–2 luzes
- [ ] Aumentar resolução (ex: 1920×1080)
- [ ] (Opcional) exportar PNG com `stb_image_write.h`
- [ ] (Opcional) anti-aliasing: múltiplos raios por pixel, média das cores

---

## Estrutura de Ficheiros

```
RayTracerCPU/
├── Makefile
├── PLANO.md
├── README.md
├── include/
│   ├── Vec3.h
│   ├── Ray.h
│   ├── Hittable.h
│   ├── Sphere.h
│   ├── Plane.h
│   ├── Light.h
│   ├── Camera.h
│   └── Material.h
├── src/
│   └── main.cpp
└── output/
    └── (imagens geradas aqui)
```

## Notas

- **Uma etapa = um conceito** — nunca misturar dois conceitos novos
- **Cada etapa produz uma imagem** — progresso visível e verificável
- **Testar sempre** — `Vec3` com valores conhecidos, imagens comparadas visualmente
- **PPM primeiro** — zero dependências, foco na aprendizagem
