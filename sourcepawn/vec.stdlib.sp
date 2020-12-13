#pragma semicolon 1
#pragma newdecls required
#include <vec.std>

public Plugin myinfo =
{
    name        = "Vector community - Standard library",
    author      = "laper32",
    description = "Standard library",
    version     = "1.0.0.0",
    url         = "vec"
}
public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
    NativesOnInit();
    return APLRes_Success;
}

inline void NativesOnInit()
{
    CreateNative("md5sum", API_MD5Sum);
    CreateNative("base64_encode", API_Base64Encode);
    CreateNative("base64_decode", API_Base64Decode);
    CreateNative("base64_mime2url", API_Base64Mine2URL);
    CreateNative("base64_url2mime", API_Base64URL2Mime);
}

// native void md5sum(const char[] str, char[] output, int maxlen)
public int API_MD5Sum(Handle plugin, int numParams)
{
    char inputStr[512]; // just a template, it shouldn't have too low limitation...
    GetNativeString(1, inputStr, sizeof(inputStr));

    int maxlen = GetNativeCell(3);
    if (!maxlen) return ThrowNativeError(SP_ERROR_PARAM, "No buffer size");

    char output[32];
    MD5Sum(inputStr, output, sizeof(output));
    return SetNativeString(2, output, maxlen);
}

//native int encode(const char[] sSource, char[] sResult, int len, int sourcelen = 0)
public int API_Base64Encode(Handle plugin, int numParams)
{
    char inputStr[512]; // just a template, it shouldn't have too low limitation...
    GetNativeString(1, inputStr, sizeof(inputStr));

    char output[1024];
    GetNativeString(2, output, sizeof(output));

    int maxlen = GetNativeCell(3);
    if (!maxlen) return ThrowNativeError(SP_ERROR_PARAM, "No buffer size");

    int sourcelen = GetNativeCell(4);
    if (sourcelen < 0) return ThrowNativeError(SP_ERROR_PARAM, "Invalid buffer size");

    return Base64Encode(inputStr, output, maxlen, sourcelen);
}

// native int decode(const char[] sSource, char[] sResult, int len)
public int API_Base64Decode(Handle plugin, int numParams)
{
    char inputStr[512]; // just a template, it shouldn't have too low limitation...
    GetNativeString(1, inputStr, sizeof(inputStr));

    char output[1024];
    GetNativeString(2, output, sizeof(output));

    int maxlen = GetNativeCell(3);
    if (!maxlen) return ThrowNativeError(SP_ERROR_PARAM, "No buffer size");

    return Base64Decode(inputStr, output, maxlen);
}

// native int mime2url(const char[] sSource, char[] sResult, int len)
public int API_Base64Mine2URL(Handle plugin, int numParams)
{
    char inputStr[512]; // just a template, it shouldn't have too low limitation...
    GetNativeString(1, inputStr, sizeof(inputStr));

    char output[1024];
    GetNativeString(2, output, sizeof(output));

    int maxlen = GetNativeCell(3);
    if (!maxlen) return ThrowNativeError(SP_ERROR_PARAM, "No buffer size");

    return Base64Mime2Url(inputStr, output, maxlen);
}

// native int url2mime(const char[] sSource, char[] sResult, int len)
public int API_Base64URL2Mime(Handle plugin, int numParams)
{
    char inputStr[512]; // just a template, it shouldn't have too low limitation...
    GetNativeString(1, inputStr, sizeof(inputStr));

    char output[1024];
    GetNativeString(2, output, sizeof(output));

    int maxlen = GetNativeCell(3);
    if (!maxlen) return ThrowNativeError(SP_ERROR_PARAM, "No buffer size");

    return Base64Url2Mime(inputStr, output, maxlen);
}

// all still unable to converted into extension's functions will be converted below.

// ================================================
// Starndard Library package: Hashlib
// ================================================

// Base 64

/**********************************************************************************
 *
 * Base64 Encoding/Decoding Functions
 * All Credits to to SirLamer & ScriptCoderPro
 * Taken from http://forums.alliedmods.net/showthread.php?t=101764
 *
 ***********************************************************************************/

static const char table[] = 
  // 0000000000111111111122222222223333333333444444444455555555556666
  // 0123456789012345678901234567890123456789012345678901234567890123
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int decodeTable[] = 
{
//  0   1   2   3   4   5   6   7   8   9
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //   0 -   9
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  10 -  19
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  20 -  29
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   //  30 -  39
    0,  0,  0,  62, 0,  0,  0,  63, 52, 53,  //  40 -  49
    54, 55, 56, 57, 58, 59, 60, 61, 0,  0,   //  50 -  59
    0,  0,  0,  0,  0,  0,  1,  2,  3,  4,   //  60 -  69
    5,  6,  7,  8,  9,  10, 11, 12, 13, 14,  //  70 -  79
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24,  //  80 -  89
    25, 0,  0,  0,  0,  0,  0,  26, 27, 28,  //  90 -  99
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38,  // 100 - 109
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48,  // 110 - 119
    49, 50, 51, 0,  0,  0,  0,  0,  0,  0,   // 120 - 129
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 130 - 139
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 140 - 149
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 150 - 159
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 160 - 169
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 170 - 179
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 180 - 189
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 190 - 199
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 200 - 209
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 210 - 219
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 220 - 229
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 230 - 239
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   // 240 - 249
    0,  0,  0,  0,  0,  0                    // 250 - 256
};

/*
 * For some reason the standard demands a string in 24-bit (3 character) intervals.
 * This fill character is used to identify unused bytes at the end of the string.
 */
static const char cFillChar          = '=';

// The conversion characters between the standard and URL-compliance Base64 protocols
static const char mime_chars[]       = "+/=";
static const char url_chars[]        = "-_.";

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
inline int Base64Encode(const char[] sSource, char[] sResult, int len, int sourcelen = 0)
{
    int nLength;	// The string length to be read from the input
    int resPos;		// The string position in the result buffer

    // If the read length was specified, use it; otherwise, pull the string length from the input.
    if (sourcelen > 0) { nLength = sourcelen; }
    else { nLength = strlen(sSource); }

    // Loop through and generate the Base64 encoded string
    // NOTE: This performs the standard encoding process.  Do not manipulate the logic within this loop.
    for (int nPos = 0; nPos < nLength; nPos++) 
    {
        int cCode;

        cCode = (sSource[nPos] >> 2) & 0x3f;

        resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);

        cCode = (sSource[nPos] << 4) & 0x3f;
        if (++nPos < nLength) { cCode |= (sSource[nPos] >> 4) & 0x0f; }
        resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);

        if ( nPos < nLength ) 
        {
            cCode = (sSource[nPos] << 2) & 0x3f;
            if (++nPos < nLength) { cCode |= (sSource[nPos] >> 6) & 0x03; }

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);
        }
        else 
        {
            nPos++;
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", cFillChar);
        }

        if (nPos < nLength) 
        {
            cCode = sSource[nPos] & 0x3f;
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", table[cCode]);
        }
        else 
        {
            resPos += FormatEx(sResult[resPos], len - resPos, "%c", cFillChar);
        }
    }

    return resPos;
}

/**
 * Decodes a Base64 string.
 *
 * @param sSource		The input string in compliant Base64 format to be decoded.
 * @param sResult		The storage buffer for the decoded text strihg or binary data.
 * @param len			The maximum length of the storage buffer, in characters/bytes.
 * @return				The length of the decoded data, in bytes.
 */
inline int Base64Decode(const char[] sSource, char[] sResult, int len)
{
    int nLength = strlen(sSource);  // The string length to be read from the input
    int resPos;                     // The string position in the result buffer

    // Loop through and generate the Base64 encoded string
    // NOTE: This performs the standard encoding process.  Do not manipulate the logic within this loop.
    for (int nPos = 0; nPos < nLength; nPos++) 
    {
        int c, c1;

        c	= decodeTable[sSource[nPos++]];
        c1	= decodeTable[sSource[nPos]];

        c = (c << 2) | ((c1 >> 4) & 0x3);

        resPos += FormatEx(sResult[resPos], len - resPos, "%c", c);

        if (++nPos < nLength) 
        {
            c = sSource[nPos];

            if (c == cFillChar) break;

            c = decodeTable[sSource[nPos]];
            c1 = ((c1 << 4) & 0xf0) | ((c >> 2) & 0xf);

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", c1);
        }

        if (++nPos < nLength) 
        {
            c1 = sSource[nPos];

            if (c1 == cFillChar) break;

            c1 = decodeTable[sSource[nPos]];
            c = ((c << 6) & 0xc0) | c1;

            resPos += FormatEx(sResult[resPos], len - resPos, "%c", c);
        }
    }

    return resPos;
}

/*
 * Converts a standards-compliant Base64 string to the commonly accepted URL-compliant alternative.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The standards-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the URL-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
inline int Base64Mime2Url(const char[] sSource, char[] sResult, int len)
{
    int chars_len = sizeof(mime_chars);	// Length of the two standards vs. URL character lists
    int nLength;								// The string length to be read from the input
    int temp_char;								// Buffer character

    nLength = strlen(sSource);

    char[] sTemp = new char[nLength+1];
    // char sTemp[ nLength + 1 ]; // Buffer string

    // Loop through string
    for (int i = 0; i < nLength; i++) 
    {
        temp_char = sSource[i];

        for (int j = 0; j < chars_len; j++) 
        {
            if(temp_char == mime_chars[j]) 
            {
                temp_char = url_chars[j];
                break;
            }
        }
        sTemp[i] = temp_char;
    }
    sTemp[nLength] = '\0';
    return strcopy(sResult, len, sTemp);
}

/*
 * Converts a URL-compliant Base64 string to the standards-compliant version.
 * Note: The result will be the same length as the input string as long as the output buffer is large enough.
 *
 * @param sSource		The URL-compliant Base64 input string to converted.
 * @param sResult		The storage buffer for the standards-compliant result.
 * @param len			The maximum length of the storage buffer in characters/bytes.
 * @return				Number of cells written.
 */
inline int Base64Url2Mime(const char[] sSource, char[] sResult, int len)
{
    int chars_len = sizeof(mime_chars);	// Length of the two standards vs. URL character lists
    int nLength;                        // The string length to be read from the input
    int temp_char;                      // Buffer character

    nLength = strlen(sSource);

    char[] sTemp = new char[nLength+1];
    // char sTemp[ nLength + 1 ]; // Buffer string

    // Loop through string
    for (int i = 0; i < nLength; i++) 
    {
        temp_char = sSource[i];
        for (int j = 0; j < chars_len; j++) 
        {
            if (temp_char == url_chars[j]) 
            {
                temp_char = mime_chars[j];
                break;
            }
        }
        sTemp[i] = temp_char;
    }
    sTemp[nLength] = '\0';
    return strcopy(sResult, len, sTemp);
}

// MD5

/**
 * Calculate the md5 hash of a string.
 *
 * @param str			Input String
 * @param output		Output String Buffer
 * @param maxlen		Size of the Output String Buffer
 * @noreturn
 */
inline void MD5Sum(const char[] str, char[] output, int maxlen)
{
    int x[2], buf[4], input[64];
    int i, ii;

    int len = strlen(str);

    // MD5Init
    x[0] = x[1] = 0;
    buf[0] = 0x67452301;
    buf[1] = 0xefcdab89;
    buf[2] = 0x98badcfe;
    buf[3] = 0x10325476;

    // MD5Update
    int update[16];

    update[14] = x[0];
    update[15] = x[1];

    int mdi = (x[0] >>> 3) & 0x3F;

    if ((x[0] + (len << 3)) < x[0]) { x[1] += 1; }

    x[0] += len << 3;
    x[1] += len >>> 29;

    int c = 0;
    while (len--) 
    {
        input[mdi] = str[c];
        mdi += 1;
        c += 1;

        if (mdi == 0x40) {

            for (i = 0, ii = 0; i < 16; ++i, ii += 4)
            {
                update[i] = (input[ii + 3] << 24) | 
                            (input[ii + 2] << 16) | 
                            (input[ii + 1] <<  8) | 
                            (input[ii    ]      );
            }
            // Transform
            transform(buf, update);
            mdi = 0;
        }
    }

    // MD5Final
    int padding[64] = 
    {
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    int inx[16];
    inx[14] = x[0];
    inx[15] = x[1];

    mdi = (x[0] >>> 3) & 0x3F;

    len = (mdi < 56) ? (56 - mdi) : (120 - mdi);
    update[14] = x[0];
    update[15] = x[1];

    mdi = (x[0] >>> 3) & 0x3F;

    if ((x[0] + (len << 3)) < x[0]) { x[1] += 1; }

    x[0] += len << 3;
    x[1] += len >>> 29;

    c = 0;
    while (len--) 
    {
        input[mdi] = padding[c];
        mdi += 1;
        c += 1;

        if (mdi == 0x40) 
        {
            for (i = 0, ii = 0; i < 16; ++i, ii += 4) 
            {
                update[i] = (input[ii + 3] << 24) | 
                            (input[ii + 2] << 16) | 
                            (input[ii + 1] <<  8) | 
                            (input[ii    ]      ) ;
            }

            // Transform
            transform(buf, update);

            mdi = 0;
        }
    }

    for (i = 0, ii = 0; i < 14; ++i, ii += 4) 
    {
        inx[i] =    (input[ii + 3] << 24) | 
                    (input[ii + 2] << 16) | 
                    (input[ii + 1] <<  8) | 
                    (input[ii    ]      ) ;
    }

    transform(buf, inx);

    int digest[16];
    for (i = 0, ii = 0; i < 4; ++i, ii += 4) 
    {
        digest[ii    ] = (buf[i]        ) & 0xFF;
        digest[ii + 1] = (buf[i] >>>  8 ) & 0xFF;
        digest[ii + 2] = (buf[i] >>> 16 ) & 0xFF;
        digest[ii + 3] = (buf[i] >>> 24 ) & 0xFF;
    }

    FormatEx(output, maxlen, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        digest[0], digest[1], digest[2], digest[3], digest[4], digest[5], digest[6], digest[7],
        digest[8], digest[9], digest[10], digest[11], digest[12], digest[13], digest[14], digest[15]);
}

// linear transformation
inline void transform(int[] _buffer, int[] _input)
{
    // 4bytes.
    int a = _buffer[0], b = _buffer[1], c = _buffer[2], d = _buffer[3];

    FF(a, b, c, d, _input[ 0],  7, 0xd76aa478);
    FF(d, a, b, c, _input[ 1], 12, 0xe8c7b756);
    FF(c, d, a, b, _input[ 2], 17, 0x242070db);
    FF(b, c, d, a, _input[ 3], 22, 0xc1bdceee);
    FF(a, b, c, d, _input[ 4],  7, 0xf57c0faf);
    FF(d, a, b, c, _input[ 5], 12, 0x4787c62a);
    FF(c, d, a, b, _input[ 6], 17, 0xa8304613);
    FF(b, c, d, a, _input[ 7], 22, 0xfd469501);
    FF(a, b, c, d, _input[ 8],  7, 0x698098d8);
    FF(d, a, b, c, _input[ 9], 12, 0x8b44f7af);
    FF(c, d, a, b, _input[10], 17, 0xffff5bb1);
    FF(b, c, d, a, _input[11], 22, 0x895cd7be);
    FF(a, b, c, d, _input[12],  7, 0x6b901122);
    FF(d, a, b, c, _input[13], 12, 0xfd987193);
    FF(c, d, a, b, _input[14], 17, 0xa679438e);
    FF(b, c, d, a, _input[15], 22, 0x49b40821);

    GG(a, b, c, d, _input[ 1],  5, 0xf61e2562);
    GG(d, a, b, c, _input[ 6],  9, 0xc040b340);
    GG(c, d, a, b, _input[11], 14, 0x265e5a51);
    GG(b, c, d, a, _input[ 0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, _input[ 5],  5, 0xd62f105d);
    GG(d, a, b, c, _input[10],  9, 0x02441453);
    GG(c, d, a, b, _input[15], 14, 0xd8a1e681);
    GG(b, c, d, a, _input[ 4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, _input[ 9],  5, 0x21e1cde6);
    GG(d, a, b, c, _input[14],  9, 0xc33707d6);
    GG(c, d, a, b, _input[ 3], 14, 0xf4d50d87);
    GG(b, c, d, a, _input[ 8], 20, 0x455a14ed);
    GG(a, b, c, d, _input[13],  5, 0xa9e3e905);
    GG(d, a, b, c, _input[ 2],  9, 0xfcefa3f8);
    GG(c, d, a, b, _input[ 7], 14, 0x676f02d9);
    GG(b, c, d, a, _input[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, _input[ 5],  4, 0xfffa3942);
    HH(d, a, b, c, _input[ 8], 11, 0x8771f681);
    HH(c, d, a, b, _input[11], 16, 0x6d9d6122);
    HH(b, c, d, a, _input[14], 23, 0xfde5380c);
    HH(a, b, c, d, _input[ 1],  4, 0xa4beea44);
    HH(d, a, b, c, _input[ 4], 11, 0x4bdecfa9);
    HH(c, d, a, b, _input[ 7], 16, 0xf6bb4b60);
    HH(b, c, d, a, _input[10], 23, 0xbebfbc70);
    HH(a, b, c, d, _input[13],  4, 0x289b7ec6);
    HH(d, a, b, c, _input[ 0], 11, 0xeaa127fa);
    HH(c, d, a, b, _input[ 3], 16, 0xd4ef3085);
    HH(b, c, d, a, _input[ 6], 23, 0x04881d05);
    HH(a, b, c, d, _input[ 9],  4, 0xd9d4d039);
    HH(d, a, b, c, _input[12], 11, 0xe6db99e5);
    HH(c, d, a, b, _input[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, _input[ 2], 23, 0xc4ac5665);

    II(a, b, c, d, _input[ 0],  6, 0xf4292244);
    II(d, a, b, c, _input[ 7], 10, 0x432aff97);
    II(c, d, a, b, _input[14], 15, 0xab9423a7);
    II(b, c, d, a, _input[ 5], 21, 0xfc93a039);
    II(a, b, c, d, _input[12],  6, 0x655b59c3);
    II(d, a, b, c, _input[ 3], 10, 0x8f0ccc92);
    II(c, d, a, b, _input[10], 15, 0xffeff47d);
    II(b, c, d, a, _input[ 1], 21, 0x85845dd1);
    II(a, b, c, d, _input[ 8],  6, 0x6fa87e4f);
    II(d, a, b, c, _input[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, _input[ 6], 15, 0xa3014314);
    II(b, c, d, a, _input[13], 21, 0x4e0811a1);
    II(a, b, c, d, _input[ 4],  6, 0xf7537e82);
    II(d, a, b, c, _input[11], 10, 0xbd3af235);
    II(c, d, a, b, _input[ 2], 15, 0x2ad7d2bb);
    II(b, c, d, a, _input[ 9], 21, 0xeb86d391);

    _buffer[0] += a;
    _buffer[1] += b;
    _buffer[2] += c;
    _buffer[3] += d;
}

static inline int FF(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += (((b) & (c))  | ((~b) & (d))) + x + ac;
    a =  (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int GG(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += (((b) & (d)) | ((c) & (~d))) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int HH(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += ((b) ^ (c) ^ (d)) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}

static inline int II(int &a, int &b, int &c, int &d, int x, int s, int ac)
{
    a += ((c) ^ ((b) | (~d))) + x + ac;
    a = (((a) << (s)) | ((a) >>> (32-(s))));
    a += b;
}