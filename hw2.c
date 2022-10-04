#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>



void read_dir_filez( DIR *P_DIR,int p_level, char *p_dir);


//storing comnd line args .
struct p_args_command {


    short Ftext_Filez;
    short PrintSi_Filez;
    short Typed_Filez;
    short Minsifilez;

    char Type_Fil;
    long long minSi;
    char *Ext;
};

struct p_args_command configure_args;

char *c_base_Directory;

//we will get the filez size
off_t fsize(const char * p_name_F)
{
    struct stat st;

    if (lstat(p_name_F,&st) == 0)
        return st.st_size;

    return 0;
}

//returninf of file path with a function.

char *get_F_Name(char *p_name_F, char *p_Path)
{

    char *m = (char *)malloc(1 + strlen(p_Path) + strlen(p_name_F));
    strcpy(m, p_Path);
    strcat(m, "/");
    strcat(m, p_name_F);

    return m;
}



//Code starts here that is main function is starts from here
int main(int argc, char **argv)
{
    //ARRAY SHOULD BE GREATER THAN NUMBER 2
    DIR *P_DIR;
    if (argc < 2) {
        printf("tHE Usage: %s <dirname>\n", argv[0]);
        exit(-1);
    }
    int h;
    for (h = 1; h < argc; h++) {
        if (strcmp(argv[h], "-S") == 0) {

            configure_args.PrintSi_Filez = 2;
            printf("has size argument\n");
        }
        if (strcmp(argv[h], "-s") == 0) {
            if (argv[h + 1] == NULL || strstr(argv[h + 1], "-")) {
                printf("you should pass -s here after the maximum filez ");
                exit(-1);
            } else {

                configure_args.minSi = atoll(argv[h + 1]);
                configure_args.Minsifilez = 2;
                printf("has size lt arg : %lld \n\n", configure_args.minSi);
                h++;
            }
        }

        if (strcmp(argv[h], "-f") == 0) {
            if (argv[h + 1] == NULL || strstr(argv[h + 1], "-")) {
                printf("After -f you should pass the file format");
                exit(-1);
            } else {
                configure_args.Ext = (char *)malloc(1 + strlen(argv[h + 1]));
                strcpy(configure_args.Ext, ".");
                strcat(configure_args.Ext, argv[h + 1]);
                configure_args.Ftext_Filez = 2;
                printf("has type argument: %s\n", configure_args.Ext);
                h++;
            }
        }

        if (strcmp(argv[h], "-t") == 0) {
            if (argv[h + 1] == NULL || strstr(argv[h + 1], "-")) {
                printf("After -t you should pass either f or d");
                exit(-1);
            } else {

                configure_args.Type_Fil = 2;
                configure_args.Type_Fil = argv[h + 1][0];
                printf("has type argument: %c\n", configure_args.Type_Fil);
                if (configure_args.Type_Fil != 'd' && configure_args.Type_Fil != 'f') {
                    printf("After -t you should pass either f or d");
                    exit(-1);
                }
                h++;
            }
        }
    }

    c_base_Directory = argv[1];

    P_DIR = opendir(c_base_Directory);
    if (P_DIR == NULL) {
        printf("Error opening directory '%s'\n", c_base_Directory);
        exit(-1);
    }
    // int count = 1;

    read_dir_filez(P_DIR, 0, "");
    closedir(P_DIR);
    return 0;
}




//A Function to print the size of the file
void file_size(char *c_dirent, char *file_name)
{
    printf(" (%ld bytes)", fsize(get_F_Name(c_dirent, file_name)));
}

int count = 1;

int printing_fomatt_matches(char *nn)
{
    if (configure_args.Ftext_Filez == 2) {
        char *end = strrchr(nn, '.');
        if (end && strcmp(end, configure_args.Ext) == 0)
            return 1;
        else
            return -1;
    }
    return 0;
}

void readfiles(DIR *P_DIR, int p_level, char *currDir)
{

    struct dirent *dirent;
    char c_dirent[1000] = "";
    int h;
    int printed = 0;
//  int should_Print = 0;

    while ((dirent = readdir(P_DIR)) != NULL) {
        printed = 0;
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {

            // every folders and files over here
            if (strlen(currDir) > 1) {
                strcat(c_dirent, currDir);
            } else {
                strcpy(c_dirent, c_base_Directory);
            }

            // prechecking formatto of filesz
            int ff_Result = printing_fomatt_matches(dirent->d_name);
            long long fileSize = fsize(get_F_Name(c_dirent, dirent->d_name));



            if (configure_args.Minsifilez == 2 && DT_DIR != dirent->d_type) {
                if (file_size(get_F_Name(c_dirent, dirent->d_name)), configure_args.minSi) {

                    if ((ff_Result == 0 || ff_Result == 1) &&
                            (configure_args.Type_Fil == 0 ||
                             (configure_args.Type_Fil == 2 &&
                              ((configure_args.Type_Fil == 'f' && DT_REG == dirent->d_type) || (configure_args.Type_Fil == 'd' && DT_DIR == dirent->d_type))))) {

                        printf("[%d]\t", count);
                        for (h = 0; h < p_level; h++) {
                            if (h % 2 == 0 || h == 0)
                                printf("|");
                            else
                                printf(" ");
                        }
                        printf("|-%s", dirent->d_name);
                        printf(" (%lld bytes)", fileSize);
                        printf("\n");
                        count++;
                    }
                }
            } else {


                if (ff_Result == 0 || ff_Result == 1 || DT_DIR == dirent->d_type) {

                    if (

                        configure_args.Typed_Filez == 0 ||
                        (configure_args.Typed_Filez == 2 &&
                         ((configure_args.Type_Fil == 'f' && DT_REG == dirent->d_type) || (configure_args.Type_Fil == 'd' && DT_DIR == dirent->d_type)))) {
                        printf("[%d]\t", count);
                        for (h = 0; h < p_level; h++) {
                            if (h % 2 == 0 || h == 0)
                                printf("|");
                            else
                                printf(" ");
                        }
                        if (configure_args.PrintSi_Filez == 2) {
                            printf("|-%s", dirent->d_name);
                            file_size(c_dirent, dirent->d_name);
                            printed = 2;

                        } else {

                            printf("|-%s", dirent->d_name);
                            printed = 2;
                        }
                    }
                }



                if (printed == 2) {
                    printf("\n");
                    count++;
                }

                strcat(c_dirent, "/");
                strcat(c_dirent, dirent->d_name);


                if (DT_DIR == dirent->d_type) {
                    DIR *ddir = opendir(c_dirent);
                    if (ddir != NULL) {

                        read_dir_filez(ddir, p_level + 2, c_dirent );
                        closedir(ddir);
                    }
                }
            }
        } else {
            if (configure_args.Typed_Filez == 0 || (configure_args.Typed_Filez == 2 && configure_args.Type_Fil == 'd')) {
                //filesssssssss
                printf("[%d]\t", count);
                for (h = 0; h < p_level; h++) {
                    if (h % 2 == 0 || h == 0)
                        printf("|");
                    else
                        printf(" ");
                }
                printf("|-%s\n", dirent->d_name);
                count++;
            }
        }
    }
}