# Windows release integrity

SUPER LIBRARY currently uses a **zero-cost release integrity workflow** based on SHA-256 plus GitHub Artifact Attestations.

The project does not currently require a paid Authenticode certificate in order to publish a release.

The public repository contains documentation and binary releases; the proprietary application source is built locally.

## Current no-cost release model

The release process is:

1. Build and test the application locally from the trusted private project source.
2. Generate `SUPER_LIBRARY_Setup_v1.0.3.exe`.
3. Create a **Draft GitHub Release** for `v1.0.3`.
4. Upload the installer to the draft.
5. Run **Actions -> Attest Windows Draft Release**.
6. The workflow downloads the exact installer bytes from the draft.
7. It computes SHA-256.
8. It creates a signed GitHub/Sigstore artifact attestation.
9. It verifies the attestation from this repository.
10. It uploads the `.sha256.txt` and `.VERIFY.txt` files to the draft release.
11. Download the installer from the draft and perform a clean-install smoke test.
12. Publish the release only after the test passes.

Artifact attestations are available for this public repository without purchasing a Code Signing certificate.

## Important limitation

GitHub Artifact Attestations are **not Microsoft Authenticode**.

The attestation proves that the exact installer bytes were processed and attested by the official `L3X4RS/super-library-snes9x` GitHub workflow. Because the application is compiled locally from private source, the attestation deliberately does **not** claim that GitHub Actions compiled the application.

Without a trusted Authenticode certificate, Windows may still show:

- `Unknown publisher`;
- Microsoft Defender SmartScreen warnings for a new/low-reputation binary.

That limitation is expected and must not be hidden from users.

## Workflow

The free workflow is:

`.github/workflows/attest-windows-draft-release.yml`

It requires **no paid provider credentials and no repository secrets**.

The workflow refuses to operate on a release that is not a draft. It does not modify the installer; it hashes and attests the exact uploaded bytes.

The custom predicate is documented in:

`docs/LOCAL_RELEASE_ATTESTATION.md`

Predicate type:

`https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1`

## Verify the installer

Install GitHub CLI and run:

```powershell
gh attestation verify .\SUPER_LIBRARY_Setup_v1.0.3.exe --repo L3X4RS/super-library-snes9x --predicate-type https://github.com/L3X4RS/super-library-snes9x/attestations/local-release/v1
```

Verify SHA-256 independently:

```powershell
Get-FileHash .\SUPER_LIBRARY_Setup_v1.0.3.exe -Algorithm SHA256
```

Compare the result with the `.sha256.txt` file attached to the same GitHub Release.

## Optional Authenticode in the future

When budget permits, a trusted OV Code Signing certificate can be added later. At that point the preferred order becomes:

`build -> sign installed binaries -> build installer -> sign installer -> verify -> SHA-256 -> GitHub attestation -> publish`

A paid certificate is an enhancement to Windows publisher identity; it is not a prerequisite for the current GitHub release integrity process.

## Security rules

- Never upload private keys, PFX files, certificate passwords, TOTP secrets or signing credentials to the repository.
- Keep the release as a draft until integrity verification and clean-install testing succeed.
- Never replace a published installer silently under the same release without updating its checksum and attestation.
- Do not describe the installer as Authenticode-signed unless `Get-AuthenticodeSignature` actually reports a valid trusted signature.
