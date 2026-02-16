Param(
    [string]$Root = "c:\Users\student3\source\repos\DX_GAME\Source"
)
$patterns = '*.cpp','*.c','*.h','*.hpp','*.inl'
$utf8 = [System.Text.Encoding]::UTF8
$sjis = [System.Text.Encoding]::GetEncoding(932)
$bomBytes = @(0xEF, 0xBB, 0xBF)

Get-ChildItem -Path $Root -Recurse -Include $patterns | ForEach-Object {
    try {
        $bytes = [System.IO.File]::ReadAllBytes($_.FullName)
    } catch {
        Write-Output ("SKIP (read error): {0}" -f $_.FullName)
        continue
    }

    # UTF-8 BOM チェック
    $hasBom = $bytes.Length -ge 3 -and $bytes[0] -eq 0xEF -and $bytes[1] -eq 0xBB -and $bytes[2] -eq 0xBF

    if ($hasBom) {
        try {
            # BOM 付き UTF-8 として読み込み
            $text = $utf8.GetString($bytes)
            # Shift-JIS に変換して書き込み（BOM なし）
            $convertedBytes = $sjis.GetBytes($text)
            [System.IO.File]::WriteAllBytes($_.FullName, $convertedBytes)
            Write-Output ("Converted: {0}" -f $_.FullName)
        } catch {
            Write-Output ("ERROR (convert failed): {0}" -f $_.FullName)
        }
    } else {
        Write-Output ("SKIP (no UTF-8 BOM): {0}" -f $_.FullName)
    }
}
