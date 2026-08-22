# Windows Code Signing

SUPER LIBRARY public Windows releases should be signed with a real Authenticode code-signing certificate before the GitHub Release is published.

The public repository does not contain the proprietary application source code. Signing is therefore split into two layers:

1. Build the application locally using the trusted project source.
2. Sign the Windows release artifact with SSL.com eSigner before publishing the GitHub Release.

## Recommended certificate

Use an SSL.com Code Signing certificate enrolled in **eSigner for Code**. eSigner keeps the private key in SSL.com's cloud HSM and exposes it to standard Windows signing tools through eSigner CKA.

For SUPER LIBRARY, an OV Code Signing certificate is appropriate. The repository itself must never contain certificate passwords, TOTP secrets, private keys or exported PFX files.

## GitHub repository secrets

After the SSL.com certificate is active and enrolled in eSigner, open:

`Settings -> Secrets and variables -> Actions -> New repository secret`

Create these four secrets:

- `SSL_ESIGNER_USERNAME`
- `SSL_ESIGNER_PASSWORD`
- `SSL_ESIGNER_TOTP_SECRET`
- `SSL_ESIGNER_MODE`

For production signing, `SSL_ESIGNER_MODE` should normally be:

`product`

Never commit these values to the repository.

## Signing a v1.0.3 installer

1. Build and test the Windows package locally.
2. Create a **Draft** GitHub Release with tag `v1.0.3`.
3. Attach the unsigned installer to that draft using this exact default name:

   `SUPER_LIBRARY_Setup_v1.0.3.exe`

4. Open `Actions -> Sign Windows Draft Release`.
5. Choose `Run workflow`.
6. Confirm the tag and asset name.
7. The workflow will:
   - refuse to operate on a release that is not a draft;
   - download SSL.com's eSigner CKA;
   - authenticate with repository secrets;
   - load the cloud-backed code-signing certificate;
   - sign the installer with Authenticode SHA-256;
   - request an RFC 3161 timestamp from `http://ts.ssl.com`;
   - verify the resulting signature with SignTool and PowerShell;
   - generate a SHA-256 checksum;
   - replace the draft asset with the signed installer;
   - attach the checksum file to the same draft release.
8. Download the signed installer from the draft and perform a clean-install smoke test.
9. Only then publish the GitHub Release.

## Important: sign installed executables too

Signing the outer Setup is important, but a complete Windows release should also sign the executable files that the installer places on disk, especially:

- `SuperLibrary.exe`
- `SNESCore.dll`
- `Uninstall SUPER LIBRARY.exe`

The correct order is:

`build -> sign installed binaries -> build installer -> sign installer -> verify -> SHA-256 -> publish`

The current public GitHub workflow signs the final installer layer. The locally generated public binaries should therefore also be Authenticode-signed before the final installer is produced whenever the release signing environment is available.

## Verification on Windows

You can verify a signed file with PowerShell:

```powershell
Get-AuthenticodeSignature .\SUPER_LIBRARY_Setup_v1.0.3.exe | Format-List
```

A correctly trusted release should report `Status : Valid`.

You can also verify with SignTool:

```bat
signtool verify /pa /all /v SUPER_LIBRARY_Setup_v1.0.3.exe
```

Generate the release checksum with:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```

## Security rules

- Never upload a PFX/private key to GitHub.
- Never put eSigner credentials in a BAT, YAML file, issue, release note or commit.
- Keep the release as a draft until signature verification succeeds.
- Do not publish an unsigned replacement under the same release tag.
- If the signing workflow fails, leave the release as draft and investigate before publishing.
