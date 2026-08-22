# Local Release Attestation v1

Predicate type:

`https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1`

This attestation is used for SUPER LIBRARY Windows installers that are built locally from the private project source and then uploaded to a **Draft GitHub Release**.

The GitHub Actions workflow downloads the exact release asset, computes its SHA-256, creates a signed GitHub/Sigstore attestation for those bytes, verifies that attestation, and publishes the checksum plus verification instructions back to the draft release.

The predicate records:

- release tag;
- asset filename;
- SHA-256;
- file size;
- repository;
- repository commit associated with the workflow run;
- workflow run ID.

## What this attestation proves

It proves that the exact artifact bytes identified by the attestation were processed and attested by the official `L3X4RS/super-library-snes9x` GitHub repository workflow.

## What it does not prove

It does **not** claim that GitHub Actions compiled the application. The application source is private and the Windows installer is built locally before it is uploaded to the draft release.

It also does **not** provide Microsoft Authenticode publisher identity. Until a trusted Code Signing certificate is adopted, Windows may still display `Unknown publisher` or SmartScreen warnings.

## Verification

For the current release asset:

```powershell
gh attestation verify .\SUPER_LIBRARY_Setup_v1.0.3.exe --repo L3X4RS/super-library-snes9x --predicate-type https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1
```

SHA-256 can be checked independently:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```
