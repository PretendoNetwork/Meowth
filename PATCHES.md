## `ssl_verify_cert_chain`
- can be identified by `ssl_client` string (string is also used in .data, safe to ignore)
- patch first error check to always take, but return 1 instead of 0 in the error case, problem solved!

## `X509_verify_cert`
- Chromium calls this directly because screw you
- just replace the whole function with `li r3, 1; blr`
