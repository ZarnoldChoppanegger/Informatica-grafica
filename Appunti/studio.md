# Rappresentazioni del contorno B-Rep (Boundary representation)

## Mesh poligonali

L'oggetto é definito dalle facce che lo delimitano (triangoli) e le relazioni tra:
* vertici
* spigoli
* facce

Si definisce **poliedro** un insieme di poligoni tali che due e solo due di essi si intersechino in uno spigolo e sia possibile **percorrerne la superficie** spostandosi da una faccia all'altra attraversando i suoi spigoli finché tutti i poligoni siano stati percorsi da questo **cammino continuo**.

Un **poliedro semplice** é un poliedro che puó essere deformato rispettando la continuitá di una sfera.
Per i poliedri semplici vale la **regola di Eulero:** `V - E + F = 2` dove:
* V -> numero di vertici
* E -> numero di spigoli
* F -> numero di facce

Un **poliedro regolare** é un poliedro semplice, le cui facce hanno lo stesso numero h di spigoli, tutti i vertici hanno lo stesso numero k di spigoli incidenti e questi sono tutti della stessa lunghezza.
Gli unici poliedri regolari sono: tetraedro, cubo, ottaedro, dodecaedro, icosaedro.

Questo tipo di rappresentazione mediante mesh permette di rappresentare poliedri, superfici aperte e anche superfici non poliedrali.

Le mesh contengono informazioni:
* **geometriche** (vertici, spigoli, facce)
* **topologiche** (relazioni di connessione tra componenti geometriche)

## Rappresentazioni mesh

Spesso é necessario eseguire query sulle mesh, per avere informazioni riguardanti la geometria e la topologia delle componenti.
Strutture dati differenti per rappresentare le mesh, permettono di effettuare certe query in maniera efficiente.

### Rappresentazione semplice

* Le facce vengono rappresentate come terne di triplette di coordinate cartesiane `T = {(ax, ay, az), (bx, by, bz), (cx, cy, cz)}`

SVANTAGGI:
* Ripetizione degli stessi vertici
* Ricerche di incidenza onerose
* Confronti tra vertici uguali possono fallire per problemi approssimazione numeri in virgola mobile

```c++
struct Faccia {
    float a[3] {};
    float b[3] {};
    float c[3] {};
};
```

### Rappresentazione con lista di vertici

* Si crea una lista di vertici (senza ripetizioni). Le facce saranno costituite da puntatori ai vertici della lista di vertici.

```c++
struct Vertice {
    float x {};
    float y {};
    float z {};
};

struct Faccia {
    Vertice *v1 {};
    Vertice *v2 {};
    Vertice *v3 {};
};
```

* Le ricerche di incidenza sono ancora onerose.

### Rappresentazione con lista di spigoli

* Si crea una lista di vertici, e ogni spigolo é rappresentato da quattro puntatori (due agli spigoli e due alle facce incidenti sullo spigolo).
* Le facce sono costituite dai puntatori agli spigoli che lo delimitano

```c++
struct Vertice {
    float x {};
    float y {};
    float z {};
};

struct Spigolo {
    Vertice *vertici[2] {};
    Faccia *facce[2] {};
};

struct Faccia {
    Spigolo *s1 {};
    Spigolo *s2 {};
    Spigolo *s3 {};
}; 
```
* Si semplifica la ricerca di incidenza spigolo-faccia

### Rappresentazione winged-edge

* Ogni spigolo é **orientato** e contiene oltre ai vertici, due puntatori alle facce incidenti e quattro puntatori agli spigoli che toccano le facce
* Ogni vertice contiene le sue coordinate e un puntatore a uno degli spigoli incidenti
* Una faccia é definita da uno degli spigoli che vi incide

```c++
struct Spigolo {
    // Puntatori a vertici
    Vertice *v_bottom {};
    Vertice *v_top {};

    // PUntatori a facce
    Faccia *f_left {};
    Faccia *f_right {};

    // Puntatori a spigoli
    Spigolo *left_pos {};
    Spigolo *left_neg {};
    Spigolo *right_pos {};
    Spigolo *right_neg {};    
};

struct Vertice {
    // Coordinate
    float x {};
    float y {};
    float z {};

    // Puntatore a spigolo incidente
    Spigolo *spigolo {};
};

struct Faccia {
    // Puntatore a uno degli spigoli incidenti
    Spigolo *spigolo {};
};
```
* Ricerca ancora piú efficiente (es. tutte le facce incidenti in un vertice)

### Rappresentazione half-edge

* Ogni spigolo é diviso in due spigoli orientati di verso opposto
* Lo spigolo é rappresentato con i puntatori al vertice di partenza e finale, il puntatore allo spigolo gemello, il puntatore allo spigolo successivo e il puntatore alla faccia a cui appartiene
* Ogni vertice contiene un puntatore ad un qualsiasi dei mezzi spigoli uscenti
* Ogni faccia contiene uno qualsiasi dei suoi mezzi spigoli

```c++
struct HE_Spigolo {
    Vertice *v1 {};
    Vertice *v2 {};

    HE_Spigolo *spigolo_gemello {};
    HE_Spigolo *spigolo_successivo {};

    Faccia *faccia {};
};

struct Spigolo {
    float x {};
    float y {};
    float z {};

    HE_Spigolo *spigolo_uscente {};
};

struct Faccia {
    HE_Spigolo *spigolo {};
};
```

* Le query sono piú efficienti della winged-edge

### Rappresentazioni implicite

* Rappresentazione di curva/superficie come luogo dei punti dove una funzione si annulla

### Rappresentazioni parametriche

* Rappresentazione di curva/superficie in forma parametrica

### Proprietá:
* **Dominio:** buono
* **Validitá:** difficile da validare (Eulero)
* **Completezza:** si
* **Unicitá:** no

### Vantaggi
* Facile ottenere informazioni sui singoli elementi
* Facile rappresentare il solido
* É possibile ottenere viste con eliminazione delle parti nascoste
* É una **rappresentazione completa**

### Svantaggi
* Richiede notevole spazio di memoria
* Editing diretto difficile
* Non é una **rappresentazione unica**

## Rappresentazioni wireframe

### Vantaggi
* Permettono di ottenere rappresentazioni 2D
* Richiedono basso costo computazionale
* Permettono diversi tipi di visualizzazione (viste ortogonali, prospettiche e multiple)
* Sono facili da modificare

### Svantaggi
* Si possono creare rappresentazioni ambigue o prive di senso
* Sono difficili da interpretare
* Geometria povera
* Non si capisce quali siano le linee non visibili
* Mancanza di standard

# Rappresentazioni Volumetriche

## Per decomposizione
I solidi sono ottenuti dalla de-composizione di questi in volumi elementari che possono avere varie forme e orientazioni. Vi sono diversi schemi:
* **Decomposizione in celle**
* **Enumerazione per occupazione spaziale**
* **Partizione spaziale binaria**

### Decomposizione in celle
Il solido é descritto da piú solidi di diversa natura (tetraedri, poliedri semplici, solidi piú complessi), di diverse dimensioni e orientazione, collegati tra di loro da un **operatore di gluing**

### Occupazione per enumerazione spaziale
Viene definita una griglia regolare nello spazio tridimensionale e ogni cella di questa griglia viene riempita interamente da un solido oppure no. (es. modello voxel-based).

### Rappresentazione spaziale binaria
Suddivisione di una regione in n sottoregioni equidirette. A queste n sottoregioni viene riapplicato lo schema in modo ricorsivo. 
I metodi BSP sono:
* **quad-tree (2D):** partizionamento in 4 quadrati
* **octree (3D):** partizionamento ricorsivo in 8 cubi. Nell'albero tutti i nodi avranno 8 figli e ciascuno di questi avrá un codice identificativo:
    * conteuto nel solido
    * esterno al solido
    * parzialmente contenuto nel solido

L'enumerazione spaziale e la rappresentazione spaziale binaria **rispettano la proprietá dell'unicitá**.

Queste rappresentazioni per decomposizione richiedono una grande quantitá di memoria.

## Costruttive

**Ma non ho sbatti**

# Algoritmi su mesh

## Bounding Box
Parallelepipedo che contiene l'oggetto.

* **AABB:** axis alligned bounding box. Si itera sui vertici trovando il min e max. Se l'oggetto si muove vanno ricalcolati.
* **OOBB:** object oriented bounding box. Il parallelepipedo é allineato con gli assi principali dell'oggetto. Il calcolo é piú complesso.

## Semplificazione Mesh

### Decimazione dei vertici
Si selezionano vertici "poco importanti" e si ri-tringola il vuoto risultante. Il criterio di scelta dei vertici é di diradare le zone a bassa curvatura

### Contrazione iterativa degli spigoli
Agli spigoli viene assegnato un costo della contrazione dello spigolo stesso. Lo spigolo con il costo minore viene rimosso e vengono ricalcolati i costi dei restanti spigoli. Una metrica semplice é la seguente: || P1 - P2|| / (1 - nl * nr).

Cioé vengono rimossi gli spigoli piúcorti nelle zone a bassa curvatura.

Questa tecnica viene utilizzata per aumentare l'efficienza del sottosistema geometrico, ovvero vengono molteplici rappresentazioni dell'oggetto a diverse risoluzioni del mesh.

### Marching cubes
Permette di ricavare, a partire da una **rappresentazione voxel**, una **mesh di triangoli**. L'algoritmo marcia su ciascun voxel e su ognuno di essi itera sui vertici determinando quali tra essi appartiene alla superficie del solido e quali no.

Ciascun cubo viene indicizzato con 8 bit, classificandolo ad una categoria. A questo punto da una tabella di 256 possibili casi (riconducibili a 15 per simmetria) si estrae la triangolazione corrispondente del cubo.

### Convex Hull (inviluppo inverso)
É il piú piccolo insieme convesso che contiene un insieme N di punti 3D.

1. Si costruisce un tetraedro con i primi 4 punti di N
2. Si eliminano i punti che cadono allinterno del convex hull corrente. Si sceglie uno dei punti p rimanenti e si determinano le facce visibili da p, come se ci fosse una luce che illumina il mesh.
3. Si determinano gli spigoli dell'orizzonte, ovvero gli spigoli che separano una faccia visibile da una non visibile.
4. Per ogni spigolo dell'orizzonte si costruisce una faccia.
5. Si eliminano le facce non visibili e si torna al punto 2 se ci sono altri punti da elaborare.

# Proiezioni

## Proiezioni parallele
> Il centro di proiezione tende all'infinito

* Tutte le linee sono sempre parallele
* Gli oggetti più lontani non sono visti più piccoli
* Vengono usate nel disegno tecnico per verificare l'allineamento delle linee e confrontare le dimensioni degli oggetti
* Il view-plane è un parallelepipedo

* **Proiezioni ortografiche:** la direzione delle rette di proiezione è ortogonale al piano di proiezione
* **Proiezioni assonometriche:** il piano di proiezione non è ortogonale a nessuno degli assi principali

## Proiezioni prospettiche
> Il centro di proiezione ha distanza finita dal view-plane

* Non tutte le linee saranno parallele tra loro e alcune tenderanno verso il centro di proiezione
* Gli oggetti avranno una dimensione più "realistica", cioè quelli più lontani saranno visti più piccoli di quelli più vicini
* Il view-plane sarà rappresentato da un tronco di piramide
* In disegno tecnico si categorizzano queste proiezioni in base al numero dei punti di fuga principali (da uno a tre)

`N° punti di fuga = N° assi principali intersecati dal view-plane`

Le **trasformazioni prospettiche e parallele** possono essere espresse in coordinate omogenee mediante una matrice 4x4 (vai a vedere da slide 07_17).

## Schema completo della pipeline grafica

![schema] (https://en.wikipedia.org/wiki/File:3D-Pipeline.png)

### Modeling transformation
Le coordinate 3D locali di un oggetto vengono convertite nelle coordinate 3D del mondo, cioè gli oggetti vengono collocati nella scena attuale.

## Proiezioni prospettiche 

### Viewing transformation
Tutti gli elementi della scena vengono convertiti nel sistema di riferimento della telecamera virtuale.

`World space -> Eye space`

### Lighting

### Projection transformation
Trasforma il view volume in un cubo con gli spigoli che puntano in (1, 1, 1) e (-1, -1, -1).

### Clipping e divisione prospettica
In questa fase vengono eliminati dalla rappresentazione finale gli oggetti che non sono visibili nella scena. Per fare ciò si esaminano le coordinate di ciascun elemento e si vede se appartengono al viewing-volume oppure no. I punti che appartengono a questo spazio vengono poi normalizzati mediante divisione prospettica.

### Viewport trasformation
Le coordinate della scena (da -1.0 a 1.0) vengono trasformate in coordinate relative alla viewport, cioè alla target area dello schermo.
Mapp la faccia del cubo su una immagine di dimensione nx * ny pixel. Ma per definizione i pixel sono quadrati di dimensione 1 centrati nell'origine. Quindi bisogna applicare una matrice di scala e trasformazione.

### Rasterisation
Shading interno ai poligoni, texture mapping, Zbuffer, stencil....

**N.B.**
>Trasformazioni di modellazione: cambiamento di posizione, scala, rotazione degli oggetti rispetto alle coordinate del mondo
>Trasformazioni di vista: cambiamento della prospettiva, ovvero del sistema di riferimento ma gli oggetti rimangono immutati

* Il clipping viene eseguito dopo la projection transformation perché si hanno delle equazioni piú semplici
* la divisione prospettica viene eseguita dopo il clipping per evitare casi di clipping scorretto

# Algoritmi pipeline grafica

> Rasterizzazione: conversione di un'immagine 2D "continua" in un'immagine 2D "discreta" dovuta alla griglia di pixels.

## Algoritmi di scan conversion

Calcolano le coordinate dei pixel che giacciono o sono vicini a una linea infinitamente sottile. La sequenza di pixel deve giacere il piú vicino possibile alla linea ideale ed essere il piú dritta possibile.

## Eliminazione di superfici nascoste

Il clipping viene applicato prima della scan-conversion. Seleziona la parte di scena da visualizzare e i modelli in questa vengono divisi in parti visibili e non visibili.

### Point clipping
Si valutano le coordinate x, y del punto rispetto ai punti "minimale" e "massimale" della finestra.

### Line clipping
Si valutano le coordinate x, y dei **due punti estremi** del segmento rispetto ai bordi della finestra.

**Fasi:**
* **fase 1: individua i tipi di segmenti rispetto alla window**
  * determinati:
    * totalmente/parzialmente visibili
    * non visibili
      * x1 and x2 < xl || x1 and x2 > xr
      * y1 and y2 < yb || y1 and y2 > yt
* **fase 2: effettua il clipping dei segmenti calcolati nel passo precedente individuando le intersezioni con i lati della finestra**

### Algoritmo di Cohen Sutherland

**Fase 1:** ad ogni estremo dei segmenti si assegna un codice a 4 bit, con il seguente significato:

* bit 1 a 1 il segmento é strettamente sopra la window
* bit 2 a 1 il segmento é strettamente sotto la window
* bit 3 a 1 il segmento é strettamente a destra della window
* bit 4 a 1 il segmento é strettamente a sinistra della window

**Fase 2:** si esegue il bitwise and di tutti i bit per categorizzare ciascun segmento: 
* entrambi gli estremi hanno codice 0000 -> il segmento é interamente visibile (termina algoritmo)
* un estremo ha codice uguale a 0000, l'altro ha codice diverso da 0000 -> parzialmente visibile
* entrambi gli estremi hanno codice diverso da 0000 -> indeterminato (parzialmente visibile o invisibile)

In tutti questi tre casi il bitwise AND logico restituisce un codice uguale a 0000. Se questo codice é diverso allora il segmento composto dai due estremi, non é visibile nella finestra.

**Fase 3:** occorre determinare le porzioni visibili dei segmenti parzialmente visibili o indeterminati:
* almeno uno dei due estremi si deve trovare fuori dalla finestra, sia esso P1
* si esaminano i bit del codice di P1 nell'ordine **bit4, bit3, bit2, bit1**
* il primo bit che si trova a 1, si calcola il punto di intersezione **I** del segmento P1P2 con il bordo della finestra
* si sostituisce **I** a P1 e si ripete l'algoritmo di Cohen dalla fase 1 fino a quando tale segmento non diventa totalmente visibile o invisibile

Per trovare il punto di intersezione di risolve il sistema di equazioni cartesiane del segmento e delle rette che delimitano la window.
> x = x1 + t(x2 - x1)
> y = y1 + t(y2 - y1) 0 <= t <= 1

### Midpoint subdivision

Si itera sul segmento calcolando il punto medio fino a quando questo non interseca i contorni della finestra

## Polygon Clipping

### Algoritmo di Sutherland-Hodgeman

* **INPUT:** sequenza di vertici che definiscono i segmenti del poligono
* esamina le relazioni tra i vertici e preso un lato del rettangolo di clipping si individuano le intersezioni con i segmenti del poligono
* **OUTPUT:** nuova sequenza di vertici
* si ripete per tutti i lati del rettangolo di clipping

![sutterlanf-hodgeman.png]()

Lo **svantaggio** di questo algoritmo é che per poligoni concavi si generano segmenti spuri che vanno eliminati con una ulteriore analisi.

### Algoritmo di Weiler-Atherton

* si calcolano le intersezioni e si marcano in verde vertici dove il poligono entra nella finestra di clipping, in blu quelli dove il poligono esce dalla finestra di clipping
* partendo dal primo vertice entrante si percorrono i contorni, in senso antiorario, con le seguenti regole:
  * se il vertice é verde (entrante), percorri i contorni del poligono fino al prossimo vertice
  * se il vertice é blu (uscente), percorri i contorni della finestra fino al prossimo vertice
* quando si ritorna al vertice di partenza, significa che si é identificata la parte di poligono visibile
* ripetere i passaggi su tutti i veritici entranti

Questo algoritmo puó essere implementato mediante un **grafo di connessione dei vertici**, costruito nel seguente modo:
* si identificano diversi tipi di nodi per (vertici del poligono, vertici di intersezione (entranti e uscenti), vertici del rettangolo di clipping)
* percorrere i vertici del poligono e inserire gli archi, includendo le intersezioni
* percorrere i vertici della finestra di clipping e inserire gli archi, includendo le intersezioni

Ora per ricavare i sottopoligoni visibili nella finestra di clipping, bisogna visitare il grafo nel seguente modo:
* partendo dal primo vertice entrante seguire il cammino che porta ai vertici del poligono
* appena si incontra un vertice uscente, da quello percorrere il cammino che porta ai vertici della finestra di clipping
* quando si ritorna al vertice di partenza si ha una porzione del poligono clippato
* si ripete la visita partendo dal vertice entrante successivo

## Clipping di curve e superfici

Per fare il clipping di curve 2D si puó fare uso di una **bounding box** contenente la curva. Se la bounding box si trova all'interno della viewing window allora la curva é totalmente visibile. Se la bounding box é all'esterno allora non é visibile. Se invece é parzialmente visibile, allora bisogna risolvere un sistema algebrico NON lineare per calcolare le intersezioni.

Per i poligoni 3D, il clipping non é altro che un'estensione dell'algoritmo Cohen-Sutherland. I codici che identificano la posizione dei veritici ora sono a 6 bit (27 regioni), questo perché si trovano in uno spazio 3D e vi é un viewing-volume a delimitare lo spazio visibile da quello non visibile.


# Rimozione superfici nascoste

**Motivazioni:**
* dare alla scena 3D maggiore realismo
* eliminare ambiguitá nella percezione di profonditá

**Distinzioni:**
* **Back-face culling:** non mostrare le facce nascoste di un poligono
* **Rimozione di superfici nascoste:** non mostrare gli oggetti che sono coperti da altri

## Back-face culling

Siccome si hanno modelli con facce planari e il vettore normale di queste facce ha sempre direzione esterna al modello, allora le facce visibili saranno quelle che avranno il vettore in direzione dell'osservatore.

**Algoritmo:** si prende il vettore normale (n) di quella faccia e un qualsiasi vettore (v) che dalla faccia va in direzione dell'osservatore. Se il prodotto scalare n\*v é > 0 allora la faccia é visibile dall'osservatore.

**N.B.** in OpenGL il back-face culling determina se una faccia é visibile (front) o no in base all'ordinamento dei vertici.

Questo ovviamente é applicabile ad un solo modello per volta e non permette di eliminare superfici occluse, cioé nascoste da altri oggetti.

## Rimozione superfici nascoste

É quindi necessaria una fase successiva per rimuovere superfici occluse.
Si ha la possibilitá di lavorare in due spazi distinti:
* **object space (spazio oggetto)**
* **image space (spazio immagine)**

### Object space

Si lavora nello spazio dei modelli 3D.

La scena viene vista com un insieme di modelli geometrici. Dati due modelli A e B, le relazioni tra essi possono essere le seguenti:
* A nasconde B
* B nasconde A
* A e B non si coprono a vicenda
* A copre parzialmente B
* B copre parzialmente A

Per gli ultimi 2 casi é necessario determinare le **sottoregioni visibili**. Per farlo si applica alla scena di K poligoni la proiezione 3D -> 2D. Per ogni i = 1,2,...,k si confronta l'i-esimo poligono con ognuno dei poligoni restanti e si determina la parte visibile.

La complessitá dell'algoritmo é **O(k²)**, quindi é consigliabile usarlo solo quando nella scena vi sono pochi poligoni.

### Image space

Si lavora nella spazio immagine della scena proiettata e per ogni pixel si determina quale é l'oggetto piú vicino all'osservatore.

**Algoritmo:** si considera una retta che passa per il centro di proiezione e la pixel window, si calcolano le intersezioni della retta con gli oggetti e si accende il rispettivo pixel del colore dell'oggetto piú vicino.

Il costo di tale algoritmo é **O(n * m * k)** con k numero di poligoni, n * m risoluzione della window ma quest'ultima é sempre costante quindi il costo é **O(k)**. Il costo rimane comunque alto perché si ha una costante di proporzionalitá alta (n * m).

## Algoritmo Depth-Sort

Come l'algoritmo del pittore, l'obiettivo é qello di disegnare (rasterizzare) prima i poligoni che stanno piú lontani dall'osservatore e successivamente disegnare quelli che stanno piú vicino.

I poligoni vanno quindi ordinati in base alla profonditá dall'osservatore. Si avranna i seguenti casi di ordinamento:
* z min di P > z max di Q, quindi P precede Q
* z min di P <= z max di Q, allora si verifica che le bounding box di P e Q sul piano xy non interferiscono. Nel caso non interferiscano P e Q possono essere visualizzati in qualsiasi ordine
* se tutti i vertici di P si trovano dalla parte opposta del piano identificato da Q, allora P precede Q
* se tutti i vertici di Q stanno dalla stessa parte dell'osservatore rispetto al piano identificato da P, allora Q precede P
* altrimenti se le proiezioni di P e Q sul piano immagine non interferiscono, allora P precede Q
* se tutti i test precedenti danno esito negativo allora si procede allo scambio di P con Q nell'ordinamento e, all'esecuzione dei test

Esistono casi critici, come la sovrapposizione ciclica di poligoni, per i quali non esiste alcun ordine di prioritá. La soluzione é calcolare le intersezioni o suddividerli in sottopoligoni.

Questo algoritmo é efficiente per scene poco complesse (con bassa probabilitá di interferenza).

## Algoritmo Z-Buffer

É un esempio di algoritmo image-space, usato da OpenGL. 

Questo algoritmo richiede due aree di memoria:
* **Frame buffer:** contiene i colori dei pixel 
* **Z-Buffer:** contiene i valori di profonditá dei poligoni

All'inizio il frame buffer viene inizializzato con il colore di background, mentre lo z-buffer a 0, cioé il **back clipping plane**.
Per ogni poligono in ordine casuale, si determinano i **pixel della sua proiezione sul piano di proiezione** e per ogni pixel del poligono in esame si calcola la coordinata z. Se z é maggiore di quella presente nello z-buffer, allora quest'ultima viene sovrascritta e anche nel frame buffer viene scritto il colore del pixel, altrimenti si lascia invariato.

**N.B.** (I valori di z diminuiscono all'aumentare della distanza dall'osservatore)

## Algoritmo di Scan-line

**NON CI HO CAPITO NULLA!**

## Ray Casting

**Guarda gli esempi delle equazioni parametriche**

# Illuminazione

> **Eq. di Kajiya:** la luce visibile in un punto é data dalla somma della luce emessa e della luce riflessa. Quest'ultima per essere calcolata tiene conto di tutte le sorgenti di luce e della loro orientazione rispetto al punto. É una formulazione ricorsiva e molto onerosa da calcolare.

I metodi di illuminazione usati in computer grafica si suddividono in **modelli locali** e **modelli globali**. I primi tengono conto solo dell'effetto diretto delle sorgenti di luce trascurando le interriflessioni tra oggetti, eliminando quindi la ricorsione nell'equazione della radianza. I modelli globali invece tengono conto della natura ricorsiva ma trascurando fenomeni di interriflessione per tenere il problema trattabile.

## Modello di Phong
É un modello di illuminazione globale, che tiene conto di 2 componenti diverse:

* **DIFFUSA / riflessione Lambertiana:** la luce proviene da una singola direzione e le superfici sono diffuse, cioé hanno la proprietá di riflettere la luce uniformemente in tutte le direzioni (gesso, legno, luna...), quindi l'angolo dal quale si osserva il materiale non é rilevante, cioé che conta é l'angolo con il quale la luce raggiunge il materiale. Questo perché l'angolo determina l'area che la stessa quantitá di luce coprirá. Maggiore sará l'area, minore sará l'intensitá luminosa. Come si calcola l'angolo? Si prende il normale al piano, il vettore di direzione della luce e si calcola il coseno tra questi `n * v = |n| * |v| * (cos¬nv)`. Se il `cos` dell'angolo é 1 allora significa che la superficie considerata riceverá il 100% di luce, altrimenti per valori minori si fará la percentuale. Se i vettori sono normalizzati il calcolo del coseno é immediato ![cos](http://slideplayer.com/slide/8347684/26/images/10/ANGLE+BETWEEN+TWO+PLANES.jpg).
> red = M_diffR * L_diffR * (max(0, normal * light_dir))
> green = M_diffG * L_diffG * (max(0, normal * light_dir))
> blue = M_diffB * L_diffB * (max(0, normal * light_dir))

* **AMBIENTALE:** componente il cui obiettivo é simulare sorgenti di luce riflesse. Questa aggiunge altri due coefficienti di **riflfessione ambientale** e **intensitá della luce ambientale**.

Materiali con superfici diffuse sono pochi, la maggiorparte dei materiali hanno anche una **componente speculare**, vale a dire che parte della luce che ricevono viene assorbita e riflessa in direzioni casuali, mentre una buona parte viene riflessa in una direzione specifica, quindi si avranno zone di maggiore **lucentezza** e altre di minore lucentezza, a prescindere dalla posizione dell'osservatore.

Come si calcolano queste zone di maggiore/minore lucentezza?
* si prende il vettore punto di riflessione - osservatore
* si prende il vettore di riflessione della luce
* si normalizzano i vettori e si calcola l'angolo tra i due
* se il coseno dell'angolo é 1, allora la luce é riflessa nella stessa direzione dell'osservatore, altrimenti é riflessa in direzione diversa

Il `cos` peró decrementa lentamente e scende anche sotto lo zero, producendo un punto luce molto ampio. Phong quindi propose di usare una **potenza del coseno**, facendo quindi decrescere la funzione molto velocemente e tenendo gli intervalli della y compresi tra 0 e 1. L'esponente é a discrezione del programmatore e viene chiamato **coefficinete di lucentezza**.

![cos](https://cglearn.codelight.eu/images/seminar/light/cosinePower.gif)

> red = M_ambientR * L_ambientR + M_diffR * L_diffR + M_specR + L_specR * (max(0, normal * light_dir)^lucentezza)
> green = M_ambientG * L_ambientG + M_diffG * L_diffG + M_specG + L_specG * (max(0, normal * light_dir)^lucentezza)
> blue = M_ambientB * L_ambientB + M_diffB * L_diffB + M_specB + L_specB * (max(0, normal * light_dir)^lucentezza)

Questo modello viene semplificato dal **modello di Bill-Phong**, nel quale si calcola un vettore H che biseca i vettori di direzione della luce e quello punto-osservatore. Nel calcolo della luce totale emessa si calcola l'angolo tra N e H. 
Questo ha il vantaggio di essere efficienti quando la luce e l'osservatore sono distanti da un punto poiché H si puó considerare costante per tutti i punti di un oggetto.
` H = L + V / |L + V|`

* **COMPONENTE EMISSIVA:** l'oggetto ha luce propria, é una componente additiva e non illumina altri oggetti.
* **COEFFICIENTE DI ATTENUAZIONE:** si introduce maggiore realismo con questo. Diminuisce con il quadrato della distanza della luce dall'oggetto.

## TIPI DI SORGENTI DI LUCE

* **PUNTIFORME (OpenGL):** sorgenti di luce che si distinguono in:
  * **Directional Light:** sorgente di luce a distanza infinita, raggi paralleli definita da una direzione e intensitá
  * **Point Light:** sorgente di luce con posizione e intensitá definite
  * **Spot Light:** sorgente di luce con posizione , direzione, intensitá e angolo di apertura definiti

* **FILIFORME**
* **SUPERFICIALE**

## Ray Tracing

É una tecnica ricorsiva nella quale si tracciano raggi uscenti dal centro di proiezione e passanti per ogni pixel dell'immagine. Se il raggio interseca un oggetto, in quel punto si traccia un nuovo raggio verso la fonte di luce. Se quest'ultimo dovesse intersecare un'altro oggetto, si ha che il punto di partenza é in ombra e si traccia un altro raggio dall'ultimo punto incontrato, ripetendo quindi il processo fatto in precedenza.
Con lo stesso principio si possono aggiungere anche **raggi di riflessione** e **raggi di rifrazione** (per oggetti trasparenti).

Questo algoritmo é computazionalmente molto costoso ed é utilizzato principalmente per applicazioni non real-time.

## Radiosity

É una tecnica per rendering di superfici perfettamente diffuse. La scena viene suddivisa in patches e di ciascuna di queste si calcola il **fattore di forma**, cioé quanta energia che esce da una patch si trasferisce su un'altra patch. Il risultato é indipendente dalla posizione dell'osservatore, ma il calcolo é costoso.

# Ombre geometriche

Le ombre possono essere **statiche** o **dinamiche**. Nel primo caso, quindi per oggetti statici, le ombre possono essere precalcolate creando una **light map** la quale si sovrapporrá alla scena e alle texture.

## Shadow Buffer

Si calcola lo Z-buffer (shadow buffer) dal punto di vista della luce. Se questa é un luce di tipo spot si calcola un solo z-buffer. Se la luce é puntiforme la si  considera racchiusa in un cubo, e quindi si calcolano 6 z-buffer, uno per ogni faccia. Nella fase di rendering, dato un qualsiasi punto che si vuole disegnare, lo si trasforma nel sistema di riferimento della luce e si trova il rispettivo valore zl nello shadow-buffer. Se questo valore é minore della z del punto nelo z-buffer, allora il punto é in ombra, in quanto esiste un oggetto che blocca la luce per quel punto.
L'algoritmo funziona anche per piú di una luce ambientale.

## Shadow Volume

Preso un poligono, di questo si individuano i contorni. Partendo dalla sorgente luminosa si costruisce il volume d'ombra, che é un tronco di piramide semi infinita, il cui vertice é la sorgente di luce. Per capire quali sono gli oggetti in ombra e quali no, si esegue un **pass test** nel seguente modo:
* se le facce **anteriori** del poligono in esame non sono nello shadow volume, si **decrementa** il valore nello stencil buffer
* se le facce **posteriori** del poligono in esame non sono nello shadow volume, si **incrementa** il valore nello stencil buffer

![shadow-volume-example] (http://ogldev.atspace.co.uk/www/tutorial40/shadow_volume1.jpg)

# Shading

Definizione del colore di ogni singolo pixel di un poligono. Definisce la **modalitá** con cui viene calcolata l'**illuminazione all'interno dei poligoni**.

Rispetto alle tecnice point-based di metodi di illuminazione globale, le tecniche di shading sono piú efficienti ma comunque computazionalmente costose se le scene sono composte da tanti poligoni.

## Constant Shading

Stesso valore di intensitá per ogni punto di un oggetto costituito da tanti poligoni.

* **VANTAGGIO:** calcolo veloce
* **SVANTAGGIO:** poco realistico

## Faceted Shading

Stesso valore di intensitá per ogni punto di un poligono, ma diverso da poligono a poligono.

* **VANTAGGIO:** calcolo veloce
* **SVANTAGGIO:** scarso realismo

## Shading interpolato

Ai vertici estremi dei poligoni si calcola l'illuminazione locale e a tutti i vertici del poligono si assegna lo stesso vettore normale. Successivamente si interpolano i valori di intensitá nei punti intermedi. Il problema di questa soluzione é che si ha un effetto di discontinuitá ai bordi di due poligoni adiacenti.

## Gouraud Shading


# Curve Parametriche

Una curva viene definito come un luogo di infiniti punti nel piano. Operativamente peró le curve vengono rappresentate con un numero finito di punti detti **punti di controllo**. Applicando delle formule/criteri a questi punti si puó ottenere la forma generale delle curve.



