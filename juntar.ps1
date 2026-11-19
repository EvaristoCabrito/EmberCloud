# Puts the split files back together (GitHub takes no file over 100 MiB): every <name>.part001 .. -> <name>, checked against PARTES.json.
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$man = Get-Content (Join-Path $here "PARTES.json") -Raw | ConvertFrom-Json
foreach ($p in $man.PSObject.Properties) {
  $rel = $p.Name; $m = $p.Value
  $out = Join-Path $here ($rel -replace "/", "\")
  if ((Test-Path $out) -and ((Get-Item $out).Length -eq $m.size)) { continue }
  Write-Host "Juntando $rel ($($m.parts) partes)..."
  $tmp = "$out.tmp"
  $fs = [System.IO.File]::Create($tmp)
  try {
    for ($i = 1; $i -le $m.parts; $i++) {
      $part = "$out.part{0:D3}" -f $i
      $bytes = [System.IO.File]::OpenRead($part)
      try { $bytes.CopyTo($fs, 16MB) } finally { $bytes.Dispose() }
    }
  } finally { $fs.Dispose() }
  if ((Get-Item $tmp).Length -ne $m.size) { Remove-Item $tmp; throw "$rel: o tamanho nao bate" }
  $h = (Get-FileHash $tmp -Algorithm SHA256).Hash.ToLower()
  if ($h -ne $m.sha256) { Remove-Item $tmp; throw "$rel: o SHA-256 nao bate" }
  Move-Item -Force $tmp $out
}
Write-Host "Tudo junto."
