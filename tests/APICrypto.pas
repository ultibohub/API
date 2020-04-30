{
Ultibo Crypto API Test unit.

Copyright (C) 2020 - SoftOz Pty Ltd.

Arch
====

 <All>

Boards
======

 <All>

Licence
=======

 LGPLv2.1 with static linking exception (See COPYING.modifiedLGPL.txt)
 
Credits
=======

 Information for this unit was obtained from:

 
References
==========

 

Crypto API
==========

 This unit uses the WebStatus framework to display test result for crypto API functions
 
 To use this unit include and register WebStatus and then register this unit by doing:
 
  HTTPListener.RegisterDocument('',TWebStatusAPICrypto.Create);
  
 Where HTTPListener is the nname of the THTTPListener instance you created for WebStatus.

}

{$mode delphi} {Default to Delphi compatible syntax}
{$H+}          {Default to AnsiString}
{$inline on}   {Allow use of Inline procedures}

unit APICrypto;

interface

uses GlobalConfig,GlobalConst,GlobalTypes,Platform,Threads,HTTP,WebStatus,Crypto,SysUtils;

{==============================================================================}
{Global definitions}
{--$INCLUDE ..\core\GlobalDefines.inc}

{==============================================================================}
{const}
 {API Crypto specific constants}
 
{==============================================================================}
{type}
 {API Crypto specific types}

{==============================================================================}
type
 {API Crypto specific clases}
 TWebStatusAPICrypto = class(TWebStatusCustom)
 public
  {}
  constructor Create;
 protected
  {Internal Methods}
  function DoContent(AHost:THTTPHost;ARequest:THTTPServerRequest;AResponse:THTTPServerResponse):Boolean; override;
 end;
 
{==============================================================================}
{var}
 {API Crypto specific variables}

{==============================================================================}
{Initialization Functions}

{==============================================================================}
{API Crypto Functions}
 
{==============================================================================}
{API Crypto Helper Functions}
function BytesToString(Data:PByte;Size:LongWord):String;
function StringToBytes(const Value:String;Data:PByte;Size:LongWord):Boolean;

function BuildBytes(Data:PByte;Size:LongWord):Boolean;

function StringTrim(const Value:String;Size:LongWord):String;

{==============================================================================}
{==============================================================================}

implementation

{==============================================================================}
{==============================================================================}
{var}
 {API Crypto specific variables}
 
{==============================================================================}
{==============================================================================}
{TWebStatusAPICrypto}
constructor TWebStatusAPICrypto.Create;
begin
 {}
 inherited Create('Crypto API','/cryptoapi',2)
end;

{==============================================================================}

function TWebStatusAPICrypto.DoContent(AHost:THTTPHost;ARequest:THTTPServerRequest;AResponse:THTTPServerResponse):Boolean; 
const
 AESGCMTestVectors:array[1..32,1..2] of String = (
 ('3A', '03C32E0E9D7E07A410B9BEE40A8F0D26'),
 ('26AE', '3A635BBDC1A17CA40B58CEEA78105CDC'),
 ('142FAC', '7E8922E8FA6F1E41E4339F0B52176DE4'),
 ('20C1863F', 'A1D12620C22EA7A0AA0E74667A20B8E1'),
 ('B3B796AA54', '53F0F9F03791BBD76BC99D1B5639F3C0'),
 ('FDCFF8EA82D8', 'B56076B42E3EEAC73DD42FC83B9220F9'),
 ('4695E719E67849', 'B4A1A2E29AAD713D5677CF425E65A400'),
 ('EE5BA3309D417697', '146EA95CED151F8C40DF98C1CC54930B'),
 ('13FF05ABB084FA608F', '55550AADC3461CC190CA22F29C6246CD'),
 ('008B0102208A22D3A562', '7178534BC7145754BAE525CC06E14A6B'),
 ('3536DBBB07B026E78E94C8', 'AB27183AEA2240B0166D702EEB2A7BFA'),
 ('00739D5A27AE82AC7D6A40EC', '4354578C3D241074D3C1F6496420F239'),
 ('DA41A5F458400C94B84026C052', 'DC6CB036FCAE9765A69F5B8C38B0B767'),
 ('4C99797C7EDCEA9D5425565522E2', '3FFEEC557F0D5FA73472D2A3F8E71389'),
 ('D381E7AD2E5BE2C97FB4BD958BC2EB', '6BF713D4E7DA7C4290967A1D23F97EDD'),
 ('5016C127F16A4787734AF3A3E6F6F0F7', '8CD8458531E94BC8160E2176F63F8D0B'),
 ('BDF3D0F24D9415AB5CF9B87BB45B4A8AE4', 'D81A3D56451313742ACE53D41223F6AF'),
 ('68C1FCBE22FBDB296C246F2E34D871A6902E', '7AFD64D4EB0DE7E2A842B518AC6D483F'),
 ('7D8D3C31E643611B0B557F29B437F635FE3FD0', '8501B61DBF4A4DD19B87E95055B95962'),
 ('4185EEB0B9B480F69B3EC7A162810073A36AD95A', 'B9BCA6D9CA0AC2B4B35D7BFF4DB27D25'),
 ('F991F4A481E322FEEC6FE9302D010AC4C811B23B4A', '54FA4DDA92E57509F4D48D206A03624F'),
 ('B288424FF96596B2A30A1EB9480F5EADC2F6D8551B9A', '2C998C8DFDC7663C8DE677B2F1CBCB57'),
 ('1066FE3DCB9F8AE0DC0693F7179F111E0A7A1FFE944FF4', '65402D1F8AFBDC819D6D1ADB5375AFD0'),
 ('0A8772CCDE122EFF01D7C187C77F07BDA50997B4320CD0D8', 'F55823AFC3D9FE6E749E70E82C823925'),
 ('E6E2FBB3E2238BC8CB396F463C2F488B4B4933087728D39815', 'F06DA35A9AEE65F9AD0DAD5B99AB4DF6'),
 ('569BD39CB1693CB89B88923ABE0D8CFA0B4F22A48A15E2EACD4A', '661AF51FF0E0E363406AB278BFC9176D'),
 ('199EED81C2428170EB089060FF9676596EADD2270895A0C8650903', '90AA9C634469D45E7BDD9AB955B90130'),
 ('B5200497A0654009B9F5B0D45FFDCF192F3042D6B05C6D6A8191A7EA', '71F6C4982AA50705D5FFC60512FC674C'),
 ('E39DA262C0E851B5CB5BD55A8B19D0AC0ABDC6FF3F32DF3B1896242D9E', 'B58AA05F594FC9779E185353CC52B8FB'),
 ('AF349B91BAD4BE2F2D5E4DDE28A1AA74115A9059A5EBBF9E38F341DC368B', '966B04FE43A2A9D94004E756F7DBFEFA'),
 ('8C87861DFFDE72FA64E926BF741330F64E2B30837650F309A3F979AE43BA2E', 'A5C825AE1B844D6A8D531077C881BD36'),
 ('924E178A17FA1CA0E7486F0404123B91DBF797BB9DBDE9B1D48D5C7F53165912', '10F972B6F9E0A3C1CF9CCF56543DCA79'));

var
 Count:Integer;
 Actual:String;
 Expected:String;
 ActualTag:String;
 ExpectedTag:String;
 
 MD5Digest:TMD5Digest;
 SHA1Digest:TSHA1Digest;
 SHA256Block:TSHA256Block;
 SHA256Digest:TSHA256Digest;
 SHA384Block:TSHA384Block;
 SHA384Digest:TSHA384Digest;
 SHA512Block:TSHA512Block;
 SHA512Digest:TSHA512Digest;
 
 RC4Key:PByte;
 RC4Data:Pointer;
 Hash:PHashContext;
 Cipher:PCipherContext;
 
 DESECBKey:Pointer;
 DESECBData:Pointer;
 DESECBEncryptKey:TDESKey;
 DESECBDecryptKey:TDESKey;
 
 DESCBCKey:String;
 DESCBCData:String;
 DESCBCCrypt:String;
 DESCBCVector:String;
 
 DES3CBCKey:String;
 DES3CBCData:String;
 DES3CBCCrypt:String;
 DES3CBCVector:String;
 
 AESECBKey:PByte;
 AESECBData:PByte;
 AESECBAESKey:TAESKey;
 
 AESCBCKey:PByte;
 AESCBCData:PByte;
 AESCBCVector:PByte;
 
 AESCTRKey:PByte;
 AESCTRData:PByte;
 AESCTRNonce:PByte;
 
 AESGCMKey:PByte;
 AESGCMIV:PByte;
 AESGCMAAD:PByte;
 AESGCMData:PByte;
 AESGCMTag:PByte;
begin
 {}
 Result:=False;
 
 {Check Host}
 if AHost = nil then Exit;

 {Check Request}
 if ARequest = nil then Exit;

 {Check Response}
 if AResponse = nil then Exit;
 
 {MD5 Digest Tests}
 AddBold(AResponse,'MD5 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','MD5DigestString',3);
 AddItemEx(AResponse,'Value:','abc',3);
 if MD5DigestString('abc',@MD5Digest) then
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('900150983CD24FB0D6963F7D28E17F72'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);

 AddItemEx(AResponse,'Test:','MD5DigestString',3);
 AddItemEx(AResponse,'Value:','abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',3);
 if MD5DigestString('abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('8215EF0796A20BCAAAE116D3876C664A'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','MD5DigestString',3);
 AddItemEx(AResponse,'Value:','(A million repetitions of "a")',3);
 if MD5DigestString(StringOfChar('a',1000000),@MD5Digest) then
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('7707D6AE4E027C70EEA2A935C2296F21'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','MD5DigestString',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 if MD5DigestString('The quick brown fox jumps over the lazy dog',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('9e107d9d372bb6826bd81d3542a419d6'); {Source: https://en.wikipedia.org/wiki/MD5}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','MD5DigestString',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if MD5DigestString('',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('d41d8cd98f00b204e9800998ecf8427e'); {Source: https://en.wikipedia.org/wiki/MD5}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 {HMAC-MD5 Digest Tests}
 AddBold(AResponse,'HMAC-MD5 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACMD5DigestString',3);
 AddItemEx(AResponse,'Key:','key',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 if HMACMD5DigestString('key','The quick brown fox jumps over the lazy dog',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('80070713463e7749b90c2dc24911e275'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACMD5DigestString',3);
 AddItemEx(AResponse,'Key:','(An empty string)',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if HMACMD5DigestString('','',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('74e6f7298a9c2d168935f58c001bad88'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);

 AddItemEx(AResponse,'Test:','HMACMD5DigestString',3);
 AddItemEx(AResponse,'Key:','(80 repetitions of 0xaa)',3);
 AddItemEx(AResponse,'Value:','Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data',3);
 if HMACMD5DigestString(StringOfChar(#$aa, 80),'Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data',@MD5Digest) then 
  begin
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('6f630fad67cda0ee1fb1f562db3aa53e'); {Source: FPC RTL \packages\hash\tests}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 {SHA1 Tests}
 AddBold(AResponse,'SHA1 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA1DigestString',3);
 AddItemEx(AResponse,'Value:','abc',3);
 if SHA1DigestString('abc',@SHA1Digest) then
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('A9993E364706816ABA3E25717850C26C9CD0D89D'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);

 AddItemEx(AResponse,'Test:','SHA1DigestString',3);
 AddItemEx(AResponse,'Value:','abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',3);
 if SHA1DigestString('abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('84983E441C3BD26EBAAE4AA1F95129E5E54670F1'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA1DigestString',3);
 AddItemEx(AResponse,'Value:','(A million repetitions of "a")',3);
 if SHA1DigestString(StringOfChar('a',1000000),@SHA1Digest) then
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('34AA973CD4C4DAA4F61EEB2BDBAD27316534016F'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);

 AddItemEx(AResponse,'Test:','SHA1DigestString',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 if SHA1DigestString('The quick brown fox jumps over the lazy dog',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('2fd4e1c67a2d28fced849ee1bb76e7391b93eb12'); {Source: https://en.wikipedia.org/wiki/SHA-1}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA1DigestString',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if SHA1DigestString('',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('da39a3ee5e6b4b0d3255bfef95601890afd80709'); {Source: https://en.wikipedia.org/wiki/SHA-1}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 {HMAC-SHA1 Tests}
 AddBold(AResponse,'HMAC-SHA1 Digest Tests','');
 AddBlank(AResponse);

 AddItemEx(AResponse,'Test:','HMACSHA1DigestString',3);
 AddItemEx(AResponse,'Key:','key',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 if HMACSHA1DigestString('key','The quick brown fox jumps over the lazy dog',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('de7c9b85b8b78aa6bc8a7a36f70a90701c9db4d9'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACSHA1DigestString',3);
 AddItemEx(AResponse,'Key:','(An empty string)',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if HMACSHA1DigestString('','',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('fbdb1d1b18aa6c08324b7d64b71fb76370690e1d'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACSHA1DigestString',3);
 AddItemEx(AResponse,'Key:','(80 repetitions of 0xaa)',3);
 AddItemEx(AResponse,'Value:','Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data',3);
 if HMACSHA1DigestString(StringOfChar(#$aa, 80),'Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data',@SHA1Digest) then 
  begin
   Actual:=SHA1DigestToString(@SHA1Digest);
   Expected:=Lowercase('e8e99d0f45237d786d6bbaa7965c7808bbff1a91'); {Source: FPC RTL \packages\hash\tests}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 {SHA256 Tests}
 AddBold(AResponse,'SHA256 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA256DigestString',3);
 AddItemEx(AResponse,'Value:','abc',3);
 if SHA256DigestString('abc',@SHA256Digest) then
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA256DigestString',3);
 AddItemEx(AResponse,'Value:','abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',3);
 if SHA256DigestString('abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq',@SHA256Digest) then 
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('248D6A61D20638B8E5C026930C3E6039A33CE45964FF2167F6ECEDD419DB06C1'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA256DigestString',3);
 AddItemEx(AResponse,'Value:','(A million repetitions of "a")',3);
 if SHA256DigestString(StringOfChar('a',1000000),@SHA256Digest) then
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('CDC76E5C9914FB9281A1C7E284D73E67F1809A48A497200E046D39CCC7112CD0'); {Source: http://www.nsrl.nist.gov/testdata/}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA256DigestString',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if SHA256DigestString('',@SHA256Digest) then 
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855'); {Source: https://en.wikipedia.org/wiki/SHA-2}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA256DigestData',3);
 AddItemEx(AResponse,'Value:','Bytes 0x00..0x7F',3);
 SHA256Block.Size:=128;
 SHA256Block.Data:=AllocMem(SHA256Block.Size);
 SHA256Block.Next:=nil;
 BuildBytes(PByte(SHA256Block.Data),SHA256Block.Size);
 if SHA256DigestData(@SHA256Block,@SHA256Digest) then 
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('471FB943AA23C511F6F72F8D1652D9C880CFA392AD80503120547703E56A2BE5'); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/hash_tv.txt}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(SHA256Block.Data);
 
 {HMAC-SHA256 Tests}
 AddBold(AResponse,'HMAC-SHA256 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACSHA256DigestString',3);
 AddItemEx(AResponse,'Key:','key',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 if HMACSHA256DigestString('key','The quick brown fox jumps over the lazy dog',@SHA256Digest) then 
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HMACSHA256DigestString',3);
 AddItemEx(AResponse,'Key:','(An empty string)',3);
 AddItemEx(AResponse,'Value:','(An empty string)',3);
 if HMACSHA256DigestString('','',@SHA256Digest) then 
  begin
   Actual:=SHA256DigestToString(@SHA256Digest);
   Expected:=Lowercase('b613679a0814d9ec772f95d778c35fc5ff1697c493715653c6c712144292c5ad'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 
 {SHA384 Tests}
 AddBold(AResponse,'SHA384 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA384DigestData',3);
 AddItemEx(AResponse,'Value:','Bytes 0x00..0x7F',3);
 SHA384Block.Size:=128;
 SHA384Block.Data:=AllocMem(SHA384Block.Size);
 SHA384Block.Next:=nil;
 BuildBytes(PByte(SHA384Block.Data),SHA384Block.Size);
 if SHA384DigestData(@SHA384Block,@SHA384Digest) then 
  begin
   Actual:=SHA384DigestToString(@SHA384Digest);
   Expected:=Lowercase('CA2385773319124534111A36D0581FC3F00815E907034B90CFF9C3A861E126A741D5DFCFF65A417B6D7296863AC0EC17'); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/hash_tv.txt}
   
   AddItemEx(AResponse,'Expected:',StringTrim(Expected,64),3);
   AddItemEx(AResponse,'Actual:',StringTrim(Actual,64),3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(SHA384Block.Data);

 AddItemEx(AResponse,'Test:','SHA384DigestData',3);
 AddItemEx(AResponse,'Value:','Bytes 0x00..0xFF',3);
 SHA384Block.Size:=256;
 SHA384Block.Data:=AllocMem(SHA384Block.Size);
 SHA384Block.Next:=nil;
 BuildBytes(PByte(SHA384Block.Data),SHA384Block.Size);
 if SHA384DigestData(@SHA384Block,@SHA384Digest) then 
  begin
   Actual:=SHA384DigestToString(@SHA384Digest);
   Expected:=Lowercase('FFDAEBFF65ED05CF400F0221C4CCFB4B2104FB6A51F87E40BE6C4309386BFDEC2892E9179B34632331A59592737DB5C5'); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/hash_tv.txt}
   
   AddItemEx(AResponse,'Expected:',StringTrim(Expected,64),3);
   AddItemEx(AResponse,'Actual:',StringTrim(Actual,64),3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(SHA384Block.Data);
 
 {HMAC-SHA384 Tests}
 AddBold(AResponse,'HMAC-SHA384 Digest Tests','');
 AddBlank(AResponse);
  
 //To Do
 
 {SHA512 Tests}
 AddBold(AResponse,'SHA512 Digest Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','SHA512DigestData',3);
 AddItemEx(AResponse,'Value:','Bytes 0x00..0x7F',3);
 SHA512Block.Size:=128;
 SHA512Block.Data:=AllocMem(SHA512Block.Size);
 SHA512Block.Next:=nil;
 BuildBytes(PByte(SHA512Block.Data),SHA512Block.Size);
 if SHA512DigestData(@SHA512Block,@SHA512Digest) then 
  begin
   Actual:=SHA512DigestToString(@SHA512Digest);
   Expected:=Lowercase('1DFFD5E3ADB71D45D2245939665521AE001A317A03720A45732BA1900CA3B8351FC5C9B4CA513EBA6F80BC7B1D1FDAD4ABD13491CB824D61B08D8C0E1561B3F7'); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/hash_tv.txt}
   
   AddItemEx(AResponse,'Expected:',StringTrim(Expected,64),3);
   AddItemEx(AResponse,'Actual:',StringTrim(Actual,64),3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(SHA512Block.Data);

 AddItemEx(AResponse,'Test:','SHA512DigestData',3);
 AddItemEx(AResponse,'Value:','Bytes 0x00..0xFF',3);
 SHA512Block.Size:=256;
 SHA512Block.Data:=AllocMem(SHA512Block.Size);
 SHA512Block.Next:=nil;
 BuildBytes(PByte(SHA512Block.Data),SHA512Block.Size);
 if SHA512DigestData(@SHA512Block,@SHA512Digest) then 
  begin
   Actual:=SHA512DigestToString(@SHA512Digest);
   Expected:=Lowercase('1E7B80BC8EDC552C8FEEB2780E111477E5BC70465FAC1A77B29B35980C3F0CE4A036A6C9462036824BD56801E62AF7E9FEBA5C22ED8A5AF877BF7DE117DCAC6D'); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/hash_tv.txt}
   
   AddItemEx(AResponse,'Expected:',StringTrim(Expected,64),3);
   AddItemEx(AResponse,'Actual:',StringTrim(Actual,64),3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(SHA512Block.Data);
 
 {HMAC-SHA512 Tests}
 AddBold(AResponse,'HMAC-SHA512 Digest Tests','');
 AddBlank(AResponse);
 
 //To Do 
 
 {RC4 Tests}
 AddBold(AResponse,'RC4 Cipher Tests','');
 AddBlank(AResponse);
 
 {RC4 RC4EncryptData}
 AddItemEx(AResponse,'Test:','RC4EncryptData',3);
 AddItemEx(AResponse,'Key:','0x0102030405 (40 bits)',3);
 AddItemEx(AResponse,'Data:','32 bytes of 0x00 (Offset 0)',3);
 RC4Key:=AllocMem(32);
 StringToBytes('0102030405',PByte(RC4Key),5);
 RC4Data:=AllocMem(32);
 if RC4EncryptData(RC4Key,5,RC4Data,RC4Data,32,0) then 
  begin
   Actual:=BytesToString(RC4Data,32);
   Expected:='b2396305f03dc027ccc3524a0a1118a86982944f18fc82d589c403a47a0d0919'; {Source: https://tools.ietf.org/html/rfc6229}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 FreeMem(RC4Key);
 FreeMem(RC4Data);
 AddBlank(AResponse);

 {RC4 RC4EncryptData}
 AddItemEx(AResponse,'Test:','RC4EncryptData',3);
 AddItemEx(AResponse,'Key:','0x0102030405 (40 bits)',3);
 AddItemEx(AResponse,'Data:','32 bytes of 0x00 (Offset 1520)',3);
 RC4Key:=AllocMem(32);
 StringToBytes('0102030405',PByte(RC4Key),5);
 RC4Data:=AllocMem(32);
 if RC4EncryptData(RC4Key,5,RC4Data,RC4Data,32,1520) then 
  begin
   Actual:=BytesToString(RC4Data,32);
   Expected:='3294f744d8f9790507e70f62e5bbceead8729db41882259bee4f825325f5a130'; {Source: https://tools.ietf.org/html/rfc6229}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 FreeMem(RC4Key);
 FreeMem(RC4Data);
 AddBlank(AResponse);
 
 {RC4 RC4EncryptData}
 AddItemEx(AResponse,'Test:','RC4EncryptData',3);
 AddItemEx(AResponse,'Key:','0x0102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20 (256 bits)',3);
 AddItemEx(AResponse,'Data:','32 bytes of 0x00 (Offset 0)',3);
 RC4Key:=AllocMem(32);
 StringToBytes('0102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20',PByte(RC4Key),32);
 RC4Data:=AllocMem(32);
 if RC4EncryptData(RC4Key,32,RC4Data,RC4Data,32,0) then 
  begin
   Actual:=BytesToString(RC4Data,32);
   Expected:='eaa6bd25880bf93d3f5d1e4ca2611d91cfa45c9f7e714b54bdfa80027cb14380'; {Source: https://tools.ietf.org/html/rfc6229}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 FreeMem(RC4Key);
 FreeMem(RC4Data);
 AddBlank(AResponse);

 {DES Tests}
 AddBold(AResponse,'DES Cipher Tests','');
 AddBlank(AResponse);
 
 {DES CipherEncrypt}
 AddItemEx(AResponse,'Test:','CipherEncrypt(CRYPTO_CIPHER_ALG_DES)',3);
 AddItemEx(AResponse,'Key:','12345678',3);
 AddItemEx(AResponse,'Data:','This is the message to encrypt!!',3);
 AddItemEx(AResponse,'Vector:','abcdefgh',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 DESCBCKey:='12345678';
 DESCBCVector:='abcdefgh';
 DESCBCData:='This is the message to encrypt!!';
 SetLength(DESCBCCrypt,32);
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_DES,PChar(DESCBCVector),PChar(DESCBCKey),DES_KEY_SIZE);
 if Cipher <> nil then
  begin
   if CipherEncrypt(Cipher,PChar(DESCBCData),PChar(DESCBCCrypt),32) then
    begin
     Actual:=BytesToString(PByte(DESCBCCrypt),32);
     Expected:='6ca9470c849d1cc1a59ffc148f1cb5e9cf1f5c0328a7e8756387ff4d0fe46050'; {Source: http://www.tero.co.uk/des/test.php}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);
  
 {DES CipherDecrypt}
 AddItemEx(AResponse,'Test:','CipherDecrypt(CRYPTO_CIPHER_ALG_DES)',3);
 AddItemEx(AResponse,'Key:','12345678',3);
 AddItemEx(AResponse,'Data:','6ca9470c849d1cc1a59ffc148f1cb5e9cf1f5c0328a7e8756387ff4d0fe46050',3);
 AddItemEx(AResponse,'Vector:','abcdefgh',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 DESCBCKey:='12345678';
 DESCBCVector:='abcdefgh';
 DESCBCData:=StringOfChar(' ',32);
 {SetLength(DESCBCCrypt,32);} {Reuse DESCBCCrypt from above result}
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_DES,PChar(DESCBCVector),PChar(DESCBCKey),DES_KEY_SIZE);
 if Cipher <> nil then
  begin
   if CipherDecrypt(Cipher,PChar(DESCBCCrypt),PChar(DESCBCData),32) then
    begin
     Actual:=DESCBCData;
     Expected:='This is the message to encrypt!!'; {Source: http://www.tero.co.uk/des/test.php}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);
  
 {DES DESEncryptBlock}
 AddItemEx(AResponse,'Test:','DESEncryptBlock',3);
 AddItemEx(AResponse,'Key:','0x0000000000000000',3);
 AddItemEx(AResponse,'Data:','0x0000000000000000',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 DESECBKey:=AllocMem(DES_KEY_SIZE);
 DESECBData:=AllocMem(DES_BLOCK_SIZE);
 DESKeySetup(DESECBKey,DES_KEY_SIZE,@DESECBEncryptKey,@DESECBDecryptKey);
 DESEncryptBlock(DESECBData,DESECBData,@DESECBEncryptKey);
 Actual:=BytesToString(PByte(DESECBData),DES_BLOCK_SIZE);
 Expected:=Lowercase('8CA64DE9C1B123A7'); {Source: http://www.ecs.soton.ac.uk/~prw99r/ez438/vectors.txt}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(DESECBKey);
 FreeMem(DESECBData);
 AddBlank(AResponse);

 {DES DESEncryptBlock}
 AddItemEx(AResponse,'Test:','DESEncryptBlock',3);
 AddItemEx(AResponse,'Key:','0xFFFFFFFFFFFFFFFF',3);
 AddItemEx(AResponse,'Data:','0xFFFFFFFFFFFFFFFF',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 DESECBKey:=AllocMem(DES_KEY_SIZE);
 DESECBData:=AllocMem(DES_BLOCK_SIZE);
 FillChar(DESECBKey^,DES_KEY_SIZE,$FF);
 FillChar(DESECBData^,DES_BLOCK_SIZE,$FF);
 DESKeySetup(DESECBKey,DES_KEY_SIZE,@DESECBEncryptKey,@DESECBDecryptKey);
 DESEncryptBlock(DESECBData,DESECBData,@DESECBEncryptKey);
 Actual:=BytesToString(PByte(DESECBData),DES_BLOCK_SIZE);
 Expected:=Lowercase('7359B2163E4EDC58'); {Source: http://www.ecs.soton.ac.uk/~prw99r/ez438/vectors.txt}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(DESECBKey);
 FreeMem(DESECBData);
 AddBlank(AResponse);
 
 {3DES Tests}
 AddBold(AResponse,'3DES Cipher Tests','');
 AddBlank(AResponse);
 
 {3DES CipherEncrypt}
 AddItemEx(AResponse,'Test:','CipherEncrypt(CRYPTO_CIPHER_ALG_3DES)',3);
 AddItemEx(AResponse,'Key:','12345678abcdefghstuvwxyz',3);
 AddItemEx(AResponse,'Data:','This is the message to encrypt!!',3);
 AddItemEx(AResponse,'Vector:','abcdefgh',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 DES3CBCKey:='12345678abcdefghstuvwxyz';
 DES3CBCVector:='abcdefgh';
 DES3CBCData:='This is the message to encrypt!!';
 SetLength(DES3CBCCrypt,32);
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_3DES,PChar(DES3CBCVector),PChar(DES3CBCKey),DES3_KEY_SIZE);
 if Cipher <> nil then
  begin
   if CipherEncrypt(Cipher,PChar(DES3CBCData),PChar(DES3CBCCrypt),32) then
    begin
     Actual:=BytesToString(PByte(DES3CBCCrypt),32);
     Expected:='61b0cefb60b56d1885fcf647d7ebf44c9031b2f2c2c06018f5871bd6278919f7'; {Source: http://www.tero.co.uk/des/test.php}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);

 {3DES CipherDecrypt}
 AddItemEx(AResponse,'Test:','CipherDecrypt(CRYPTO_CIPHER_ALG_3DES)',3);
 AddItemEx(AResponse,'Key:','12345678abcdefghstuvwxyz',3);
 AddItemEx(AResponse,'Data:','61b0cefb60b56d1885fcf647d7ebf44c9031b2f2c2c06018f5871bd6278919f7',3);
 AddItemEx(AResponse,'Vector:','abcdefgh',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 DES3CBCKey:='12345678abcdefghstuvwxyz';
 DES3CBCVector:='abcdefgh';
 DES3CBCData:=StringOfChar(' ',32);
 {SetLength(DES3CBCCrypt,32);} {Reuse DES3CBCCrypt from above result}
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_3DES,PChar(DES3CBCVector),PChar(DES3CBCKey),DES3_KEY_SIZE);
 if Cipher <> nil then
  begin
   if CipherDecrypt(Cipher,PChar(DES3CBCCrypt),PChar(DES3CBCData),32) then
    begin
     Actual:=DES3CBCData;
     Expected:='This is the message to encrypt!!'; {Source: http://www.tero.co.uk/des/test.php}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);
 
 {AES Tests}
 AddBold(AResponse,'AES Cipher Tests','');
 AddBlank(AResponse);
 
 {AES AESEncryptBlock}
 AddItemEx(AResponse,'Test:','AESEncryptBlock (128bit)',3);
 AddItemEx(AResponse,'Key:','0x2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Data:','0x6bc1bee22e409f96e93d7e117393172a',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESECBKey),AES_KEY_SIZE128);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('6bc1bee22e409f96e93d7e117393172a',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE128,@AESECBAESKey);
 AESEncryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('3ad77bb40d7a3660a89ecaf32466ef97'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);

 {AES AESEncryptBlock}
 AddItemEx(AResponse,'Test:','AESEncryptBlock (192bit)',3);
 AddItemEx(AResponse,'Key:','0x8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b',3);
 AddItemEx(AResponse,'Data:','0x6bc1bee22e409f96e93d7e117393172a',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE192);
 StringToBytes('8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b',PByte(AESECBKey),AES_KEY_SIZE192);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('6bc1bee22e409f96e93d7e117393172a',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE192,@AESECBAESKey);
 AESEncryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('bd334f1d6e45f25ff712a214571fa5cc'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);

 {AES AESEncryptBlock}
 AddItemEx(AResponse,'Test:','AESEncryptBlock (256bit)',3);
 AddItemEx(AResponse,'Key:','0x603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4',3);
 AddItemEx(AResponse,'Data:','0x6bc1bee22e409f96e93d7e117393172a',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE256);
 StringToBytes('603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4',PByte(AESECBKey),AES_KEY_SIZE256);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('6bc1bee22e409f96e93d7e117393172a',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE256,@AESECBAESKey);
 AESEncryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('f3eed1bdb5d2a03c064b5a7e3db181f8'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);
 
 {AES AESDecryptBlock}
 AddItemEx(AResponse,'Test:','AESDecryptBlock (128bit)',3);
 AddItemEx(AResponse,'Key:','0x2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Data:','0x3ad77bb40d7a3660a89ecaf32466ef97',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESECBKey),AES_KEY_SIZE128);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('3ad77bb40d7a3660a89ecaf32466ef97',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE128,@AESECBAESKey);
 AESDecryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('6bc1bee22e409f96e93d7e117393172a'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);

 {AES AESDecryptBlock}
 AddItemEx(AResponse,'Test:','AESDecryptBlock (192bit)',3);
 AddItemEx(AResponse,'Key:','0x8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b',3);
 AddItemEx(AResponse,'Data:','0xbd334f1d6e45f25ff712a214571fa5cc',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE192);
 StringToBytes('8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b',PByte(AESECBKey),AES_KEY_SIZE192);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('bd334f1d6e45f25ff712a214571fa5cc',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE192,@AESECBAESKey);
 AESDecryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('6bc1bee22e409f96e93d7e117393172a'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);

 {AES AESDecryptBlock}
 AddItemEx(AResponse,'Test:','AESDecryptBlock (256bit)',3);
 AddItemEx(AResponse,'Key:','0x603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4',3);
 AddItemEx(AResponse,'Data:','0xf3eed1bdb5d2a03c064b5a7e3db181f8',3);
 AddItemEx(AResponse,'Vector:','(None)',3);
 AddItemEx(AResponse,'Mode:','Electronic Codebook (ECB)',3);
 AESECBKey:=AllocMem(AES_KEY_SIZE256);
 StringToBytes('603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4',PByte(AESECBKey),AES_KEY_SIZE256);
 AESECBData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('f3eed1bdb5d2a03c064b5a7e3db181f8',PByte(AESECBData),AES_BLOCK_SIZE);
 AESKeySetup(AESECBKey,AES_KEY_SIZE256,@AESECBAESKey);
 AESDecryptBlock(AESECBData,AESECBData,@AESECBAESKey);
 Actual:=BytesToString(PByte(AESECBData),AES_BLOCK_SIZE);
 Expected:=Lowercase('6bc1bee22e409f96e93d7e117393172a'); {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}

 AddItemEx(AResponse,'Expected:',Expected,3);
 AddItemEx(AResponse,'Actual:',Actual,3);

 if Uppercase(Actual) = Uppercase(Expected) then
  begin
   AddItemEx(AResponse,'Result:','Correct',3);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','Incorrect',3);
  end;
 FreeMem(AESECBKey);
 FreeMem(AESECBData);
 AddBlank(AResponse);
 
 {AES CipherEncrypt}
 AddItemEx(AResponse,'Test:','CipherEncrypt(CRYPTO_CIPHER_ALG_AES)',3);
 AddItemEx(AResponse,'Key:','0x2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Data:','0x6bc1bee22e409f96e93d7e117393172a',3);
 AddItemEx(AResponse,'Vector:','0x000102030405060708090A0B0C0D0E0F',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 AESCBCKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESCBCKey),AES_KEY_SIZE128);
 AESCBCVector:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('000102030405060708090A0B0C0D0E0F',PByte(AESCBCVector),AES_BLOCK_SIZE);
 AESCBCData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('6bc1bee22e409f96e93d7e117393172a',PByte(AESCBCData),AES_BLOCK_SIZE);
 
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_AES,PChar(AESCBCVector),PChar(AESCBCKey),AES_KEY_SIZE128);
 if Cipher <> nil then
  begin
   if CipherEncrypt(Cipher,AESCBCData,AESCBCData,AES_BLOCK_SIZE) then
    begin
     Actual:=BytesToString(AESCBCData,AES_BLOCK_SIZE);
     Expected:='7649abac8119b246cee98e9b12e9197d'; {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);
 
 {AES CipherDecrypt}
 AddItemEx(AResponse,'Test:','CipherDecrypt(CRYPTO_CIPHER_ALG_AES)',3);
 AddItemEx(AResponse,'Key:','0x2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Data:','0x7649abac8119b246cee98e9b12e9197d',3);
 AddItemEx(AResponse,'Vector:','0x000102030405060708090A0B0C0D0E0F',3);
 AddItemEx(AResponse,'Mode:','Cipher Block Chaining (CBC)',3);
 AESCBCKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESCBCKey),AES_KEY_SIZE128);
 AESCBCVector:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('000102030405060708090A0B0C0D0E0F',PByte(AESCBCVector),AES_BLOCK_SIZE);
 AESCBCData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('7649abac8119b246cee98e9b12e9197d',PByte(AESCBCData),AES_BLOCK_SIZE);
 
 Cipher:=CipherCreate(CRYPTO_CIPHER_ALG_AES,PChar(AESCBCVector),PChar(AESCBCKey),AES_KEY_SIZE128);
 if Cipher <> nil then
  begin
   if CipherDecrypt(Cipher,AESCBCData,AESCBCData,AES_BLOCK_SIZE) then
    begin
     Actual:=BytesToString(AESCBCData,AES_BLOCK_SIZE);
     Expected:='6bc1bee22e409f96e93d7e117393172a'; {Source: http://www.inconteam.com/software-development/41-encryption/55-aes-test-vectors}
     
     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);
     
     if Uppercase(Actual) = Uppercase(Expected) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
      end;
    end
   else 
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
    end;
   
   CipherDestroy(Cipher);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','CipherCreate Failed',3);
  end;  
 AddBlank(AResponse);
 
 {AES AESCTREncryptData}
 AddItemEx(AResponse,'Test:','AESCTREncryptData (128bit)',3);
 AddItemEx(AResponse,'Key:','2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Nonce:','f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff',3);
 AddItemEx(AResponse,'Data:','6bc1bee22e409f96e93d7e117393172a',3);
 AddItemEx(AResponse,'Mode:','Counter Mode (CTR)',3);
 AESCTRKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESCTRKey),AES_KEY_SIZE128);
 AESCTRData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('6bc1bee22e409f96e93d7e117393172a',PByte(AESCTRData),AES_BLOCK_SIZE);
 AESCTRNonce:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff',PByte(AESCTRNonce),AES_BLOCK_SIZE);
 if AESCTREncryptData(AESCTRKey,AES_KEY_SIZE128,AESCTRNonce,AESCTRData,AESCTRData,AES_BLOCK_SIZE) then
  begin
   Actual:=BytesToString(AESCTRData,AES_BLOCK_SIZE);
   Expected:=Lowercase('874d6191b620e3261bef6864990db6ce'); {Source: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf}

   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(AESCTRKey);
 FreeMem(AESCTRData);
 FreeMem(AESCTRNonce);
 
 {AES AESCTRDecryptData}
 AddItemEx(AResponse,'Test:','AESCTRDecryptData (128bit)',3);
 AddItemEx(AResponse,'Key:','2b7e151628aed2a6abf7158809cf4f3c',3);
 AddItemEx(AResponse,'Nonce:','f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff',3);
 AddItemEx(AResponse,'Data:','874d6191b620e3261bef6864990db6ce',3);
 AddItemEx(AResponse,'Mode:','Counter Mode (CTR)',3);
 AESCTRKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('2b7e151628aed2a6abf7158809cf4f3c',PByte(AESCTRKey),AES_KEY_SIZE128);
 AESCTRData:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('874d6191b620e3261bef6864990db6ce',PByte(AESCTRData),AES_BLOCK_SIZE);
 AESCTRNonce:=AllocMem(AES_BLOCK_SIZE);
 StringToBytes('f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff',PByte(AESCTRNonce),AES_BLOCK_SIZE);
 if AESCTRDecryptData(AESCTRKey,AES_KEY_SIZE128,AESCTRNonce,AESCTRData,AESCTRData,AES_BLOCK_SIZE) then
  begin
   Actual:=BytesToString(AESCTRData,AES_BLOCK_SIZE);
   Expected:=Lowercase('6bc1bee22e409f96e93d7e117393172a'); {Source: https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38a.pdf}

   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
  end
 else 
  begin
   AddItemEx(AResponse,'Result:','Failed',3);
  end;
 AddBlank(AResponse);
 FreeMem(AESCTRKey);
 FreeMem(AESCTRData);
 FreeMem(AESCTRNonce);
 
 {AES AESGCMEncryptData}
 AESGCMKey:=AllocMem(AES_KEY_SIZE128);
 StringToBytes('000102030405060708090a0b0c0d0e0f',PByte(AESGCMKey),AES_KEY_SIZE128);
 AESGCMTag:=AllocMem(AES_BLOCK_SIZE);
 for Count:=1 to 32 do
  begin
   AESGCMIV:=AllocMem(Count);
   StringToBytes('000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f',PByte(AESGCMIV),Count);
   AESGCMAAD:=AllocMem(Count);
   StringToBytes('000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f',PByte(AESGCMAAD),Count);
   AESGCMData:=AllocMem(Count);
   StringToBytes('000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f',PByte(AESGCMData),Count);

   AddItemEx(AResponse,'Test:','AESGCMEncryptData (128bit)',3);
   AddItemEx(AResponse,'Key:',BytesToString(AESGCMKey,AES_KEY_SIZE128),3);
   AddItemEx(AResponse,'IV:',BytesToString(AESGCMIV,Count),3);
   AddItemEx(AResponse,'AAD:',BytesToString(AESGCMAAD,Count),3);
   AddItemEx(AResponse,'Data:',BytesToString(AESGCMData,Count),3);
   AddItemEx(AResponse,'Mode:','Galois/Counter Mode (GCM)',3);
 
   if AESGCMEncryptData(AESGCMKey,AES_KEY_SIZE128,AESGCMIV,AESGCMAAD,AESGCMData,AESGCMData,Count,Count,Count,AESGCMTag) then
    begin
     Actual:=BytesToString(AESGCMData,Count);
     Expected:=Lowercase(AESGCMTestVectors[Count,1]); {Source: https://github.com/libtom/libtomcrypt/blob/develop/notes/gcm_tv.txt}

     ActualTag:=BytesToString(AESGCMTag,AES_BLOCK_SIZE);
     ExpectedTag:=Lowercase(AESGCMTestVectors[Count,2]);

     AddItemEx(AResponse,'Expected:',Expected,3);
     AddItemEx(AResponse,'Actual:',Actual,3);

     AddItemEx(AResponse,'ExpectedTag:',ExpectedTag,3);
     AddItemEx(AResponse,'ActualTag:',ActualTag,3);

     if (Uppercase(Actual) = Uppercase(Expected)) and (Uppercase(ActualTag) = Uppercase(ExpectedTag)) then
      begin
       AddItemEx(AResponse,'Result:','Correct',3);
       AddBlank(AResponse);

       System.Move(AESGCMTag^,AESGCMKey^,AES_BLOCK_SIZE);
      end
     else
      begin
       AddItemEx(AResponse,'Result:','Incorrect',3);
       Break;
      end;
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Failed',3);
     Break;
    end;

   FreeMem(AESGCMIV);
   FreeMem(AESGCMAAD);
   FreeMem(AESGCMData);
  end;
 AddBlank(AResponse);
 FreeMem(AESGCMKey);
 FreeMem(AESGCMTag);
 
 {Hash Tests}
 AddBold(AResponse,'Hash Tests','');
 AddBlank(AResponse);
 
 AddItemEx(AResponse,'Test:','HashCreate(CRYPTO_HASH_ALG_HMAC_MD5)',3);
 AddItemEx(AResponse,'Key:','key',3);
 AddItemEx(AResponse,'Value:','The quick brown fox jumps over the lazy dog',3);
 Hash:=HashCreate(CRYPTO_HASH_ALG_HMAC_MD5,PChar('key'),3);
 if Hash <> nil then
  begin
   HashUpdate(Hash,PChar('The quick brown fox jumps over the lazy dog'),43);
   HashFinish(Hash,@MD5Digest,SizeOf(TMD5Digest));
   
   Actual:=MD5DigestToString(@MD5Digest);
   Expected:=Lowercase('80070713463e7749b90c2dc24911e275'); {Source: https://en.wikipedia.org/wiki/Hash-based_message_authentication_code}
   
   AddItemEx(AResponse,'Expected:',Expected,3);
   AddItemEx(AResponse,'Actual:',Actual,3);
   
   if Uppercase(Actual) = Uppercase(Expected) then
    begin
     AddItemEx(AResponse,'Result:','Correct',3);
    end
   else
    begin
     AddItemEx(AResponse,'Result:','Incorrect',3);
    end;
   
   HashDestroy(Hash);
  end
 else
  begin
   AddItemEx(AResponse,'Result:','HashCreate Failed',3);
  end;  
 AddBlank(AResponse);
 
 {Return Result}
 Result:=True;
end;

{==============================================================================}
{==============================================================================}
{Initialization Functions}

{==============================================================================}
{==============================================================================}
{API Crypto Functions}

{==============================================================================}
{==============================================================================}
{API Crypto Helper Functions}
function BytesToString(Data:PByte;Size:LongWord):String;
var
 Count:LongWord;
begin
 {}
 Result:='';
 
 if Data = nil then Exit;
 if Size = 0 then Exit;
 
 for Count:=0 to Size - 1 do
  begin
   Result:=Result + HexStr(Data[Count],2);
  end;
 
 Result:=Lowercase(Result);
end;
 
{==============================================================================}
 
function StringToBytes(const Value:String;Data:PByte;Size:LongWord):Boolean;
var
 Count:LongWord;
 Offset:LongWord;
begin
 {}
 Result:=False;
 try
  if Data = nil then Exit;
  if Size = 0 then Exit;
  if Length(Value) = 0 then Exit;
  
  {Check Size}
  if Length(Value) < (Size * 2) then Exit;
  
  Offset:=0;
  for Count:=0 to Size - 1 do
   begin
    Data[Count]:=StrToInt('$' + Copy(Value,Offset + 1,2));
    
    Inc(Offset,2);
   end;
   
  Result:=True; 
 except
  {}
 end; 
end;

{==============================================================================}

function BuildBytes(Data:PByte;Size:LongWord):Boolean;
var
 Count:LongWord;
begin
 {}
 Result:=False;
 try
  if Data = nil then Exit;
  if Size = 0 then Exit;

  for Count:=0 to Size - 1 do
   begin
    Data[Count]:=Count;
   end;
   
  Result:=True; 
 except
  {}
 end; 
end;
  
{==============================================================================}
  
function StringTrim(const Value:String;Size:LongWord):String;
begin
 {}
 Result:=Value;
 if Length(Result) > Size then
  begin
   Result:=Copy(Result,1,Size) + '...';
  end;
end;
  
{==============================================================================}
{==============================================================================}

end.
 