#ifndef _OSL_BGM_H_
#define _OSL_BGM_H_

#ifdef __cplusplus
extern "C" {
#endif

//Le format BGM
typedef struct {
    char strVersion[11];                // "OSLBGM v01"
    int format;                            // Toujours 1
    int sampleRate;                        // Taux d'�chantillonnage
    unsigned char nbChannels;            // Mono ou st�r�o
    unsigned char reserved[32];            // R�serv�
} BGM_FORMAT_HEADER;

#ifdef __cplusplus
}
#endif

#endif

