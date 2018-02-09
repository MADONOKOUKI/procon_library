ll mul(ll a, ll b) {
  if (!b)
    return 0;
  ll res = 0;
  while (b) {
    if (b & 1)
      res = (res + a) % m;
    b >>= 1;
    a = a * 2 % m;
  }
  return res;
}
ll gcd(ll a, ll b) {
  if (!b)
    return a;
  return gcd(b, a%b);
}
ll nOk(ll n, ll k) {
  if (k > n)
    return 0;
  ll f = 1;
  for (ll i = n - k + 1; i <= n; ++i) {
    ll z = i;
    ll g = gcd(z, k);
    z /= g;
    k /= g;
    f = mul(f, z);
  }
  return f;
}
