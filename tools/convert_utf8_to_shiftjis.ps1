Param(
    [string]$Root = "c:\Users\student3\source\repos\DX_GAME\Source"
)
$patterns = '*.cpp','*.c','*.h','*.hpp','*.inl','*.txt','*.md'
Get-ChildItem -Path $Root -Recurse -Include $patterns | ForEach-Object {
    try {
        $bytes = [System.IO.File]::ReadAllBytes($_.FullName)
    } catch {
        Write-Output ("SKIP (read error): {0}" -f $_.FullName)
        continue
    }
    $utf8 = [System.Text.Encoding]::UTF8
    $decoded = $utf8.GetString($bytes)
    $reencoded = $utf8.GetBytes($decoded)
    $isUtf8 = [System.Linq.Enumerable]::SequenceEqual($bytes, $reencoded)
    if ($isUtf8) {
        $sjis = [System.Text.Encoding]::GetEncoding(932)
        $convertedBytes = $sjis.GetBytes($decoded)
        [System.IO.File]::WriteAllBytes($_.FullName, $convertedBytes)
        Write-Output ("Converted: {0}" -f $_.FullName)
    } else {
        Write-Output ("OK SJIS: {0}" -f $_.FullName)
    }
}
