Name:       vconf
Summary:    Configuration system library
Version:    0.2.51
Release:    1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    vconf-setup.service
Source2:    vconf-setup.conf
Source1001: 	vconf.manifest
Requires:	util-linux
Requires(post): /sbin/ldconfig, systemd
Requires(postun): /sbin/ldconfig, systemd
BuildRequires:  cmake
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf-internal-keys)
BuildRequires:  pkgconfig(libtzplatform-config)

%description 
Configuration system library

%package devel
Summary:    Vconf (devel)
Requires:   %{name} = %{version}-%{release}
Requires:   pkgconfig(glib-2.0)
Requires:   vconf = %{version}-%{release}
Requires:   vconf-keys-devel = %{version}-%{release}

%description devel
Vconf library (devel)

%package keys-devel
Summary:    Vconf (devel)
Requires:   %{name} = %{version}-%{release}
Requires:   vconf = %{version}-%{release}
Requires:   vconf-internal-keys-devel

%description keys-devel
Vconf key management header files

%prep
%setup -q -n %{name}-%{version}
cp %{SOURCE1001} .

%build
%cmake . \
	-DTZ_SYS_CONFIG=%{TZ_SYS_CONFIG}

make %{?jobs:-j%jobs}

%install
%make_install
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/.backup
mkdir -p %{buildroot}%{_unitdir}/basic.target.wants
mkdir -p %{buildroot}%{_prefix}/lib/tmpfiles.d
install -m0644 %SOURCE1 %{buildroot}%{_unitdir}/
install -m0644 %SOURCE2 %{buildroot}%{_prefix}/lib/tmpfiles.d/
ln -sf ../vconf-setup.service %{buildroot}%{_unitdir}/basic.target.wants/

%post
/sbin/ldconfig
systemctl daemon-reload
chsmack -a 'User' %{TZ_SYS_CONFIG}
chsmack -a 'User' %{TZ_SYS_CONFIG}/db
chsmack -a 'User' %{TZ_SYS_CONFIG}/db/.backup

%postun
/sbin/ldconfig
systemctl daemon-reload

%files
%manifest %{name}.manifest
%license LICENSE.APLv2
%defattr(-,root,root,-)
%attr(755,root,root) %{_sysconfdir}/preconf.d/vconf-setup
%{_bindir}/vconftool
%{_bindir}/vconf-init
%config(missingok) %attr(644,root,root) %{TZ_SYS_CONFIG}/kdb_first_boot
%{_libdir}/*.so.*
%dir %attr(777,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db
%dir %attr(777,root,root) %{TZ_SYS_CONFIG}/db/.backup
%{_unitdir}/basic.target.wants/vconf-setup.service
%{_unitdir}/vconf-setup.service
%{_prefix}/lib/tmpfiles.d/vconf-setup.conf

%files devel
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so

%files keys-devel
%manifest %{name}.manifest
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf-keys.h

