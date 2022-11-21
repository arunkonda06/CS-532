#include <pthread.h>

typedef struct job
{
    int jid;        /* job ID */
    pthread_t tid;  
    char *cmd;      /* job command */
    char *stat;     
    int estat;      
    char *start;    /* job start time */
    char *stop;     
    char fnout[10]; 
    char fnerr[10]; 
} job;

typedef struct queue
{
    int size;     
    job **buffer; 
    int start;    
    int end;      
    int count;    /* number of elements in the queue */
} queue;

/* job functions */
job create_job(char *cmd, int jid);
void list_jobs(job *jobs, int n, char *mode);

/* queue functions */
queue *queue_init(int n);
int queue_insert(queue *q, job *jp);
job *queue_delete(queue *q);
void queue_destroy(queue *q);

/* I/O functions and other helpers */
int get_line(char *s, int n);
int is_space(char c);
char *left_strip(char *s);
char *get_copy(char *s);
char *get_copy_until_newline(char *s);
char *current_datetime_str();
char **get_args(char *line);
int open_log(char *fn);
