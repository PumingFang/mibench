/*
 * Sphinxp -- a protocol for communicating with Sphinx over internet sockets.
 * 
 * **********************************************
 * CMU ARPA Speech Project
 *
 * Copyright (c) 1996 Carnegie Mellon University.
 * ALL RIGHTS RESERVED.
 * **********************************************
 * 
     Brian G. Milnes, Eric Thayer, Ravi Mosur
     Speech Group
     Carnegie Mellon University 
     5-Mar-95

$Log: sphinxp.h,v $
Revision 1.1.1.1  2000/01/28 22:09:07  lenzo
Initial import of sphinx2



 */


#ifndef _SPHINXP_H_
#define _SPHINXP_H_

#include <sys/types.h>

#define SPHINXP_PORT	7027	/* Default port on which the server listens */


/*
 * Message types from CLIENT to SPHINX SERVER.  Look below for packet formats.
 */

typedef enum {
    SET_LOCAL_INPUT=14,         /* Set the microphone at the server to be the A/D input. */
    SET_RAW_INPUT=1,		/* Set speech input to server to be raw A/D samples.
				   Must be sent once, before beginning any utterance
				   for which raw samples are sent to server. */
    SET_CEP_INPUT=2,		/* Set speech input to server to be cepstral frames.
				   Must be sent once, before beginning any utterance
				   for which cep frames are sent to server. */
    SET_UPDATE_FREQ=3,		/* Set frequency (#frames) with which server will report
				   partial results back to client during an utterance.
				   If the frequency is 0, server will not automatically
				   send any partial result during an utterance. */
    BEGIN_UTTERANCE=4,		/* Inform the server that we are beginning an utterance.
                                   After this message and until END_UTTERANCE is sent,
				   the client can only send CEP_FRAMES or RAW_FRAMES
				   (depending on CEP-INPUT or RAW-INPUT mode), or
				   REQUEST_PARTIAL_RESULT messages. */
    CEP_FRAMES=5,		/* Message containing cep frames data. */
    RAW_FRAMES=6,		/* Message containing raw samples data. */
    END_UTTERANCE=7,		/* Inform the server that the utterance is done.  The
				   server implicitly returns a FINAL_RESULT message */
    REQUEST_PARTIAL_RESULT=8,	/* Request partial recognition result from the server
				   while in the midst of an utterance. */
    REQUEST_FINAL_RESULT=9,	/* Request final recognition result from the server after
				   an utterance has been processed. */
    CLIENT_ERROR=10,		/* Inform the server that the client got into an error
				   state and is terminating connection. */
    LANGUAGE_MODEL = 12,        /* Specify the name of a language model for sphinx to
				   use. */
    START_SYMBOL = 13,          /* Specify a start symbol in the language model for
				   sphinx to use. */
    LMFILE_READ = 15,		/* Read a specified language model file with the given name
				   and other parameters.  Can only be called in between
				   utterances.  The LM file must exist at the server */
    LM_DELETE = 16		/* Delete the named LM from the server's collection */
} client_message_tag_t;

/*
 * Message types from SPHINX SERVER to CLIENT.  Look below for packet formats.
 */

typedef enum {
    SERVER_ERROR=1,	/* Inform the client that the server is an error state and is
			   terminating connection. */
    PARTIAL_RESULT=2,	/* Partial recognition result from server to client */
    FINAL_RESULT=3	/* Final recognition result from server to client */
} server_message_tag_t;

/*
 * Packet formats.  All pkts have the following header:
 *	32-bit <pkt_length_in_bytes including this header>
 * 	32-bit <pkt_type>
 * 
 * Individual pkt types have the following data following the header:
 * 
 * CLIENT -> SERVER:
 *   SET_RAW_INPUT
 * 	[No data]
 *   SET_CEP_INPUT
 * 	[No data]
 *   SET_UPDATE_FREQ
 * 	32-bit partial results update frequency (#frames)
 *   BEGIN_UTTERANCE
 * 	[No data]
 *   CEP_FRAMES
 * 	32-bit <#frames cep-data in this pkt>
 * 	32-bit*cep-vector-length cep-data (for #frames)
 *   RAW_FRAMES
 * 	32-bit <#samples in this pkt>
 * 	16-bit samples (for #samples)
 *   END_UTTERANCE
 * 	[No data]
 *   REQUEST_PARTIAL_RESULT
 * 	[No data]
 *   REQUEST_FINAL_RESULT
 * 	[No data]
 *   CLIENT_ERROR
 * 	[No data]
 *   SET_LOCAL_INPUT
 * 	[No data]
 *   LANGUAGE_MODEL
 * 	<namestring for language model including terminating null char>
 *   START_SYMBOL
 * 	<namestring for start symbol including terminating null char>
 *   LMFILE_READ
 * 	32-bit float <language-weight>
 * 	32-bit float <unigram-weight>
 * 	32-bit float <word-insertion-penalty>
 * 	<LM filename including terminating NULL char>
 * 	<Associated LM name including terminating NULL char>
 *   LM_DELETE
 * 	<LM name including terminating NULL char>
 * 
 * SERVER -> CLIENT:
 *   SERVER_ERROR
 * 	[No data]
 *   PARTIAL_RESULT
 * 	32-bit <frame#>
 * 	<result string including terminating null char>
 *   FINAL_RESULT
 * 	32-bit <frame#>
 * 	<result string including terminating null char>
 */

#endif
