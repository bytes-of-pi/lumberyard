// {BEGIN_LICENSE}
/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 */
// {END_LICENSE}

#include <${SysCompClass}.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace ${Namespace}
{
    void ${SysCompClass}::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<${SysCompClass}, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<${SysCompClass}>("${Name}", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void ${SysCompClass}::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("${Name}Service"));
    }

    void ${SysCompClass}::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("${Name}Service"));
    }

    void ${SysCompClass}::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        AZ_UNUSED(required);
    }

    void ${SysCompClass}::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        AZ_UNUSED(dependent);
    }

    void ${SysCompClass}::Init()
    {
    }

    void ${SysCompClass}::Activate()
    {
        ${GemRequestBus}::Handler::BusConnect();
    }

    void ${SysCompClass}::Deactivate()
    {
        ${GemRequestBus}::Handler::BusDisconnect();
    }

} // namespace ${Namespace}
