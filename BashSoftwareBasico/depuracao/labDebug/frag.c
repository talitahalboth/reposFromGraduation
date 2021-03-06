
// para ver os dados de entrada:
// od -v -w20 -tx4  frag.data | cut -c 9- | head -10

// para ver os pacotes fragmentados
// cat frag.data | ./a.out | head -10

#define	IP_RF 0x8000			/* reserved fragment flag */
#define	IP_DF 0x4000			/* dont fragment flag */
#define	IP_MF 0x2000			/* more fragments flag */
#define	IP_OFFMASK 0x1fff		/* mask for fragmenting bits */

struct ip {
  unsigned char ip_v_hl;		/* version and header length */
  unsigned char ip_tos;		        /* type of service */
  unsigned short ip_len;		/* total length */
  unsigned short ip_id;		        /* identification */
  unsigned short ip_off;		/* fragment offset field */
  unsigned char ip_ttl;	         	/* time to live */
  unsigned char ip_p;    		/* protocol */
  unsigned short ip_sum;                /* checksum */
  unsigned int ip_src, ip_dst;          /* source and dest address */
};

#define IPBUF 1024
#define FRAGBUF 32

typedef int hdr[5]; 
typedef union ip_vet {
  struct ip   i;
  hdr         v;
} ip_vet;


#define FALSE 0
#define TRUE  (! FALSE)


extern void exit(int);
extern void print(int);
extern int  readInt(int *);
extern void writeInt(int);


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *optarg;

static struct ip ip[IPBUF];


static void  my_memcpy(void *dst, const void *src, int len) {
  int i;
 
  /*
   * memcpy does not support overlapping buffers, so always do it
   * forwards. (Don't change this without adjusting memmove.)
   *
   * For speedy copying, optimize the common case where both pointers
   * and the length are word-aligned, and copy word-at-a-time instead
   * of byte-at-a-time. Otherwise, copy by bytes.
   *
   * The alignment logic below should be portable. We rely on
   * the compiler to be reasonably intelligent about optimizing
   * the divides and modulos out. Fortunately, it is.
   */
 
  if ((long)dst % sizeof(long) == 0 &&
      (long)src % sizeof(long) == 0 &&
      len % sizeof(long) == 0) {
 
    long *d = dst;
    const long *s = src;
 
    for (i=0; i < (int)(len/sizeof(long)); i++) {
      d[i] = s[i];
    }
  } else {
    char *d = dst;
    const char *s = src;
    
    for (i=0; i < len; i++) {
      d[i] = s[i];
    }
  }
  //return dst;
}


static struct ip frag[FRAGBUF];

static int fragsize;


static int in_cksum(register char *buf, register int len) {
  unsigned long sum = 0;

  while (len > 2) {
    sum += *((unsigned short *) buf);
    buf += 2;
    if ((sum & 0x80000000)!= 0)
      sum = (sum & 0xFFFF) + (sum >> 16);
    len -= 2;
  }

  if (len != 0)
    sum += (long)*buf;

  while ((sum >> 16) != 0)
    sum = (sum & 0xFFFF) + (sum >> 16);

  return (int)~sum;
}

static void print_ip(struct ip *ip) {   // little-endian version
  printf("%04x%02x%02x %04x%04x %04x%02x%02x %04x %04x\n",
  	 ip->ip_len, (unsigned int)ip->ip_tos, (unsigned int)ip->ip_v_hl, 
  	 ip->ip_off, ip->ip_id, 
    ip->ip_sum, (unsigned int)ip->ip_p, (unsigned int)ip->ip_ttl,
	 ip->ip_src, ip->ip_dst);
}


static int fragment(struct ip *ip) {
  int l;
  unsigned int f=0;

  l = (int)ip->ip_len;
  while (l > fragsize) {
    my_memcpy(&(frag[f]), ip, (int)sizeof(struct ip));
    frag[f].ip_len = (unsigned short)fragsize;
    frag[f].ip_off = (unsigned short)(((f*fragsize) >> 3) | IP_MF);
    frag[f].ip_sum = 0;
    frag[f].ip_sum = (unsigned short)in_cksum((char *)&(frag[f]), 20);
    f++;
    l-=fragsize;
  }
  my_memcpy(&(frag[f]), ip, (int)sizeof(struct ip));
  frag[f].ip_len = (unsigned short int)l;
  frag[f].ip_off = (unsigned short int)((f*fragsize) >> 3);
  frag[f].ip_sum = 0;
  frag[f].ip_sum = (unsigned short int)in_cksum((char *)&(frag[f]), 20);
  f++;

  return (int)f;
}


int main(int argc, char *argv[]) {
  int i, packets, f, j;

  fragsize = 512;

  while((i = getopt(argc,argv,"f:")) != EOF) {
    switch(i) {
    case 'f':
      fragsize = atoi(optarg);
      break;
    default:
      printf("usage: %s -f fragsize\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  if (fragsize != (fragsize & 0xfffffff8)) {
    printf("fragsize must be multiple of 8!\n");
    exit(EXIT_FAILURE);
  }

  while ((packets = (int)fread(ip, sizeof(struct ip), IPBUF, stdin)) > 0) {
    for (i=0; i<packets; i++) {
      // print_ip(&(ip[i]));   // original packet
      f = (int)fragment(&(ip[i]));
      for (j=0; j<f; j++) {
      	print_ip(&(frag[j]));  // first + fragments
      }
    }
  }
  return 0;
}

