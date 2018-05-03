Name:    mkmotd
Version: 1.0.0
Release: 1%{?dist}
Summary: Build motd out of multiple files
License: MIT

Source0: %{name}-%{version}.tar.gz

%description
Build the message of the day file out of
multiple source files.

%prep
%setup -q -c

%build
%cmake .
make %{?_smp_mflags}

%install
make install DESTDIR=%{buildroot}

%files
%{_bindir}/mkmotd
%dir %{_sysconfdir}/motd.d
%{_mandir}/man1/mkmotd.1*

%changelog
* Thu May  3 2018 Stefan Schulte <stschulte@posteo.de> - 1.0.0-1
- initial version
