/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzFramework/Asset/AssetBundleManifest.h>
#include <AzFramework/Asset/AssetRegistry.h>

namespace AZ::IO
{
    /*!
     * Events from Archive
     */
    class ArchiveNotifications
        : public AZ::EBusTraits
    {
    public:
        using MutexType = AZStd::recursive_mutex;
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
        static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

        virtual void BundleOpened([[maybe_unused]] const char* bundleName, [[maybe_unused]] AZStd::shared_ptr<AzFramework::AssetBundleManifest> bundleManifest, [[maybe_unused]] const char* nextBundle, [[maybe_unused]] AZStd::shared_ptr<AzFramework::AssetRegistry> bundleCatalog) {}
        virtual void BundleClosed([[maybe_unused]] const char* bundleName) {}

        // Sent when a file is accessed through Archive
        virtual void FileAccess([[maybe_unused]] const char* filePath) {}
    };
    using ArchiveNotificationBus = AZ::EBus<ArchiveNotifications>;

}
