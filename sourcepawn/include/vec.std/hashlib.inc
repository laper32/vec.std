#if defined _vec_std_hashlib_included
#endinput
#endif
#define _vec_std_hashlib_included

/**
 * Calculate the md5 hash of a string.
 *
 * @param str			Input String
 * @param output		Output String Buffer
 * @param maxlen		Size of the Output String Buffer
 * @noreturn
 */
native void md5sum(const char[] str, char[] output, int maxlen);

/**
 * Encodes a string or binary data into Base64
 *
 * @param sSource		The input string or binary data to be encoded.
 * @param sResult		The storage buffer for the Base64-encoded result.
 * @param len			The maximum length of the storage buffer, in characters/bytes.
 * @param sourcelen 	(optional): The number of characters or length in bytes to be read from the input source.
 *						This is not needed for a text string, but is important for binary data since there is no end-of-line character.
 * @return				The length of the written Base64 string, in bytes.
 */
native int base64_encode(const char[] sSource, char[] sResult, int len, int sourcelen = 0);

/**
 * Decodes a Base64 string.
 *
 * @param sSource		The input string in compliant Base64 format to be decoded.
 * @param sResult		The storage buffer for the decoded text strihg or binary data.
 * @param len			The maximum length of the storage buffer, in characters/bytes.
 * @return				The length of the decoded data, in bytes.
 */
native int base64_decode(const char[] sSource, char[] sResult, int len);

/**
 * Converts a standards-compliant Base64 string to the commonly accepted URL-compliant alternative.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The standards-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the URL-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
native int base64_mime2url(const char[] sSource, char[] sResult, int len);

/**
 * Converts a URL-compliant Base64 string to the standards-compliant version.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The URL-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the standards-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
native int base64_url2mime(const char[] sSource, char[] sResult, int len);