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
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/account
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/ail
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/alarm
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/allshare
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/call
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/ciss
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/contacts-svc
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/debug
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/dnet/statistics/cellular
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/dnet/statistics/wifi
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/sync
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/eas
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/face-svc
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/filemanager
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/gallery
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/idle_lock
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/isf
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/data-provider-master
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/setting
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/gps
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/supl
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/nmea
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/replay
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/last/gps
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/last/wps
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/location/last/cps
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/lockscreen
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/memo
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/menuscreen
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/mobile_hotspot
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/nfc
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/pwlock
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/rcs
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/setting
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/menu_widget
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/DevManagement
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/DS/Accounts
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/wifionly
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/pushmessage
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/autoupdate
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/sysman
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/system
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/usb
mkdir -p %{buildroot}%{TZ_SYS_CONFIG}/db/wifi
mkdir -p %{buildroot}%{_unitdir}/basic.target.wants
mkdir -p %{buildroot}%{_prefix}/lib/tmpfiles.d
install -m0644 %SOURCE1 %{buildroot}%{_unitdir}/
install -m0644 %SOURCE2 %{buildroot}%{_prefix}/lib/tmpfiles.d/
ln -sf ../vconf-setup.service %{buildroot}%{_unitdir}/basic.target.wants/

%post
/sbin/ldconfig
find %{TZ_SYS_CONFIG}/db/ -type d | xargs chsmack -a User
systemctl daemon-reload

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
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/account
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/ail
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/alarm
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/allshare
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/call
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/ciss
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/contacts-svc
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/debug
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/dnet
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/dnet/statistics
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/dnet/statistics/cellular
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/dnet/statistics/wifi
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/sync
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/eas
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/face-svc
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/filemanager
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/gallery
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/idle_lock
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/isf
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/data-provider-master
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/setting
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/gps
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/supl
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/nmea
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/replay
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/last
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/last/gps
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/last/wps
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/location/last/cps
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/lockscreen
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/memo
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/menuscreen
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/mobile_hotspot
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/nfc
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/pwlock
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/rcs
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/setting
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/menu_widget
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/DevManagement
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/DS
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/DS/Accounts
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/wifionly
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/pushmessage
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/SyncML/oma-dm-service/software_update/autoupdate
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/sysman
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/system
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/usb
%dir %attr(775,root,%TZ_SYS_USER_GROUP) %{TZ_SYS_CONFIG}/db/wifi
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

