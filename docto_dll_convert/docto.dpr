library docto;

{$R ExtraFiles.res}

uses
  SysUtils,
  Classes,
  ActiveX,
  WordUtils in 'WordUtils.pas',
  MainUtils in 'MainUtils.pas',
  ResourceUtils in 'ResourceUtils.pas',
  PathUtils in 'PathUtils.pas',
  datamodSSL in 'datamodSSL.pas',
  ExcelUtils in 'ExcelUtils.pas',
  PowerPointUtils in 'PowerPointUtils.pas',
  Word_TLB_Constants in 'Word_TLB_Constants.pas',
  Excel_TLB_Constants in 'Excel_TLB_Constants.pas',
  PowerPoint_TLB_Constants in 'PowerPoint_TLB_Constants.pas',
  VisioUtils in 'VisioUtils.pas',
  Visio_TLB in 'Visio_TLB.pas';

procedure ConvertDocTo(const inputExtension: PAnsiChar;
  const inputFile: PAnsiChar; const outputFile: PAnsiChar;
  const outputFileExtension: PAnsiChar); stdcall;
var
  Converter: integer;
  paramlist: TStringlist;
  DocConv: TWordDocConverter;
  XLSConv: TExcelXLSConverter;
  PPConv: TPowerPointConverter;
  VSConv: TVisioConverter;
  LogResult: String;
begin

  paramlist := TStringlist.create;

  try
    try
      // Due to the way config is loaded I must create all of them.
      DocConv := TWordDocConverter.create;
      XLSConv := TExcelXLSConverter.create;
      PPConv := TPowerPointConverter.create;
      VSConv := TVisioConverter.create;
      try
        begin
          paramlist.Add(string(inputExtension));
          paramlist.Add('-F');
          paramlist.Add(string(inputFile));
          paramlist.Add('-O');
          paramlist.Add(string(outputFile));
          paramlist.Add('-T');
          paramlist.Add(string(outputFileExtension));
          paramlist.Add('-Q');
        end;

        CoInitialize(nil);

        Converter := DocConv.ChooseConverter(paramlist);

        // DocConv.LogVersionInfo;
        if Converter = MSWord then
        begin
          DocConv.Log('Converter:MS Word', CHATTY);
          DocConv.LoadConfig(paramlist);
          LogResult := DocConv.Execute;
          DocConv.Log(LogResult);
        end
        else if Converter = MSEXCEL then
        begin
          // Config Level already set for DocConv but not for XLS.
          XLSConv.ChooseConverter(paramlist);
          XLSConv.Log('Converter:MS Excel', CHATTY);
          XLSConv.LoadConfig(paramlist);
          LogResult := XLSConv.Execute;
          XLSConv.Log(LogResult);
        end
        ELSE if Converter = MSPOWERPOINT then
        begin
          PPConv.ChooseConverter(paramlist);
          PPConv.Log('Converter:MS Powerpoint', CHATTY);
          PPConv.LoadConfig(paramlist);
          LogResult := PPConv.Execute;
          PPConv.Log(LogResult);
        end
        ELSE if Converter = MSVISIO then
        begin
          VSConv.ChooseConverter(paramlist);
          VSConv.Log('Converter:MS Visio', CHATTY);
          VSConv.LoadConfig(paramlist);
          LogResult := VSConv.Execute;
          VSConv.Log(LogResult);
        end;

        CoUninitialize;
      finally
        DocConv.free;
        XLSConv.free;
        PPConv.free;

      end;
    except
      on E: Exception do
      begin
        WriteLn('Exiting with Error 400: ' + E.ClassName);
        WriteLn(E.Message);
        halt(400);
      end;

    end;
  finally
    paramlist.free;
  end;
end;

exports
  ConvertDocTo;

begin

end.
