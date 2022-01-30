#ifdef cMIPS

#include "cMIPS.h"

extern void exit(int);
#define IO_READ_BOT_ADDR 1
#define IO_WRITE_BOT_ADDR 1



//cMIPS I/O functions
void print(int n) { // write to VHDL simulator's standard output
  int *IO = (int *)x_IO_BASE_ADDR;

  *IO = n;
}


int readInt(int *n) { // read integer from file, status==1 if EOF, 0 otw
  int *IO = (int *)IO_READ_BOT_ADDR;
  int status, value;

  value  = *IO;
  status = *(IO + 1);

  if (status == 0) {
    *n = value;
  }
  return status;
}

#define writeInt(c) print(c)

void writeIntXXX(int n) { // write integer to output file
  int *IO = (int *)IO_WRITE_BOT_ADDR;

  *IO = n;
}

#if 0 // not used here

void *memset(void *dst, const int val, int len) {
  register unsigned char *ptr = (unsigned char*)dst;
  int cnt;

  cnt = (int)ptr % 4;
  while( (cnt > 0) && (len > 0) ) {
    *ptr = (char)val;
    cnt--; len--;
    ptr++;
  } // ptr is now word aligned
  cnt = val | (val<<8) | (val<<16) | (val<<24);
  while(len >= 4) {
    *((int *)ptr) = cnt;
    len -= 4;
    ptr += 4;
  }
  while(len > 0) {
    *ptr = (char)val;
    len--;
    ptr++;
  }
  return(dst);
}

//Implements function bzero for cMIPS
void bzero(void *s, int bytes) {
  memset(s,'\0',bytes) ;
}

#endif


#define MALLOC_BASE_ADDRESS (x_DATA_BASE_ADDR + 0x00020000)
#define MALLOC_SIZE         0x000B0000
#define NULL 0


#else

#include <stdio.h>
#include <stdlib.h>

#endif


// begin internal malloc
/* http://www.flipcode.com/archives/Simple_Malloc_Free_Functions.shtml */




#define USED       1
 

int *myheap;

typedef struct {
  unsigned size;
} UNIT;

typedef struct {
  UNIT* free;
  UNIT* heap;
} MSYS;

static MSYS msys;

static UNIT* compact(const UNIT *p, unsigned nsize ) {
  unsigned bsize, psize;
  UNIT *best;
  
  best = p;
  bsize = 0;
  
  while((psize = p->size) != 0 ) {
    if( (psize & USED) != 0) {
      if( bsize != 0 ) {
	best->size = bsize;
	if( bsize >= nsize ) {
	  return best;
	}
      }
      bsize = 0;
      best = p = (UNIT *)( (unsigned *)p + (psize & ~USED) );
    } else {
      bsize += psize;
      p = (UNIT *)( (unsigned *)p + psize );
    }
  }
  
  if( bsize != 0 ) {
    best->size = bsize;
    if( bsize >= nsize ) {
      return best;
    }
  }
  
  return best;
}

void MSYS_Free( void *ptr ) { 
  if( ptr ) {
    UNIT *p;
    
    p = (UNIT *)( (unsigned *)ptr - sizeof(UNIT) );
    p->size &= ~USED;
  }
}


/*@null@*/void *MSYS_Alloc( unsigned size ) {
  unsigned fsize;
  UNIT *p;
  
  if( size == 0 ) 
  {
    return NULL;
  }
  
  size  += 3 + sizeof(UNIT);
  size >>= 2;
  size <<= 2;
  
  if( msys.free == 0 || size > msys.free->size ) {
    msys.free = compact( msys.heap, size );
    if( msys.free == 0 ) return 0;
  }

  p = msys.free;
  fsize = msys.free->size;
  
  if( fsize >= (unsigned)(size + sizeof(UNIT)) ) {
    msys.free = (UNIT *)( (unsigned *)p + size );
    msys.free->size = fsize - size;
  } 
  else {
    msys.free = 0;
    size = fsize;
  }

  p->size = size | USED;
  
  return (void *)( (unsigned *)p + sizeof(UNIT) );
}

#define free(p)  MSYS_Free(p)    
#define malloc(s)  MSYS_Alloc(s)

void MSYS_Init( void *heap, unsigned len ) {
  len  += 3;
  len >>= 2;
  len <<= 2;
  msys.free = msys.heap = (UNIT *) heap;
  msys.free->size = msys.heap->size = len - sizeof(UNIT);
  *(unsigned *)((char *)heap + len - 4) = 0;
}

void MSYS_Compact( void ) {
  msys.free = compact( msys.heap, 0x7fffffff );
}
// end internal malloc



#include "dijkstra_input.h"

#define NONE      9999

struct _NODE
{
  int iDist;
  int iPrev;
};
typedef struct _NODE NODE;

struct _QITEM {
  int iNode;
  int iDist;
  int iPrev;
  struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;

QITEM *qHead = NULL;

             
static int AdjMatrix[NUM_NODES][NUM_NODES];

static int g_qCount = 0;
NODE rgnNodes[NUM_NODES];
static int ch;
static int iPrev, iNode;
static int i, iCost, iDist;


static void print_path (NODE *rgnNodes, int chNode) {
  if (rgnNodes[chNode].iPrev != NONE) {
      print_path(rgnNodes, rgnNodes[chNode].iPrev);
  }
#ifdef cMIPS  
  writeInt(chNode);
#else
  printf ("%08x\n", chNode);
  fflush(stdout);
#endif
}


static void enqueue (int iNode, int iDist, int iPrev) {
  QITEM *qNew = (QITEM *) malloc(sizeof(QITEM));
  QITEM *qLast = qHead;
  
  if (!qNew) {
#ifndef cMIPS
    fprintf(stderr, "Out of memory.\n");
#endif
    exit(1);
  }
  qNew->iNode = iNode;
  qNew->iDist = iDist;
  qNew->iPrev = iPrev;
  qNew->qNext = NULL;
  
  if (qLast == NULL) {
      qHead = qNew;
  } else {
    while (qLast->qNext) qLast = qLast->qNext;
    qLast->qNext = qNew;
  }
  g_qCount++;
  // ASSERT(g_qCount);
}


static void dequeue (int *piNode, int *piDist, int *piPrev) {
  QITEM *qKill = qHead;
  
  if (qHead) {
    // ASSERT(g_qCount);
    *piNode = qHead->iNode;
    *piDist = qHead->iDist;
    *piPrev = qHead->iPrev;
    qHead = qHead->qNext;
    free(qKill);
    g_qCount--;
  }
}


static int qcount (void) {
  return(g_qCount);
}

static int dijkstra(int chStart, int chEnd) {
    
  for (ch = 0; ch < NUM_NODES; ch++) {
    rgnNodes[ch].iDist = NONE;
    rgnNodes[ch].iPrev = NONE;
  }

  if (chStart == chEnd) {
#ifdef cMIPS
    writeInt(0); writeInt(0);
#else
    printf("Shortest path is 0 in cost. Just stay where you are.\n");
#endif
  } else {
    rgnNodes[chStart].iDist = 0;
    rgnNodes[chStart].iPrev = NONE;
    
    enqueue (chStart, 0, NONE);
    
    while (qcount() > 0) {
      dequeue (&iNode, &iDist, &iPrev);
      for (i = 0; i < NUM_NODES; i++) {
	if ((iCost = AdjMatrix[iNode][i]) != NONE) {
	  if ( (NONE == rgnNodes[i].iDist) || 
	       (rgnNodes[i].iDist > (iCost + iDist)) ) {
	    rgnNodes[i].iDist = iDist + iCost;
	    rgnNodes[i].iPrev = iNode;
	    enqueue (i, iDist + iCost, iNode);
	  }
	}
      }
    }
#ifdef cMIPS
    writeInt(rgnNodes[chEnd].iDist);
    print_path(rgnNodes, chEnd);
    writeInt(-1); // path terminator
#else
    //printf("Shortest path is %d in cost. ", rgnNodes[chEnd].iDist);
    printf("%08x\n", rgnNodes[chEnd].iDist);
    //printf("Path is: ");
    print_path(rgnNodes, chEnd);
    printf("%8x\n",-1);
#endif
    }
    return 0;
}



#ifdef cMIPS
void main(void) {
#else
int main(int argc, char *argv[]) {
#endif

  int i,j,k;

#ifdef cMIPS

  myheap = (int *)MALLOC_BASE_ADDRESS;

  MSYS_Init( (void *)MALLOC_BASE_ADDRESS, (unsigned)MALLOC_SIZE );

  qHead = NULL; // MUST be initialized here  B^((
  g_qCount = 0;

#else

  myheap = calloc(4010,4);
  MSYS_Init( (void *)myheap, (unsigned)4000*4 ); // private malloc
  
  //if (argc<2) {
  //  fprintf(stderr, "Usage: dijkstra <filename>\n");
  //  fprintf(stderr, "Only supports matrix size is #define'd.\n");
  //}

  /* open the adjacency matrix file */
  //FILE *fp;
  //fp = fopen (argv[1],"r");

#endif

  /* make a fully connected matrix */
  for (i=0;i<NUM_NODES;i++) {
    for (j=0;j<NUM_NODES;j++) {
      /* make it more sparce */
      //#ifdef cMIPS
      k = mat[i][j];
      //#else
      //fscanf(fp,"%d",&k);
      //#endif
      AdjMatrix[i][j]= k;
    }
  }

  /* finds 10 shortest paths between nodes */
  for (i=0,j=NUM_NODES/2; i<(NUM_NODES/5); i++,j++) {
    j = j%NUM_NODES;
    dijkstra(i,j);
  }
  
#ifndef cMIPS
  exit(0);
#endif
}
